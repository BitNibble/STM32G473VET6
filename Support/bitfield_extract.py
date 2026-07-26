import re
import collections

def generate_peripheral_bitfields_bulletproof(header_path, prefix="RCC", output_h_path=None):
    prefix = prefix.strip().upper()

    try:
        with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Error: File '{header_path}' not found.")
        return

    # Step 1: Intermediate Holding Place
    rcc_line_pattern = re.compile(rf'^#define\s+{prefix}_\w+.*', re.MULTILINE)
    prefix_lines = rcc_line_pattern.findall(content)
    
    if not prefix_lines:
        print(f"No macros found for prefix {prefix}_")
        return
        
    intermediary_holding_place = "\n".join(prefix_lines)

    # Step 2: Parse Positions
    pos_pattern = re.compile(rf'#define\s+({prefix}_([A-Za-z0-9]+)_([A-Za-z0-9_]+))_Pos\s+\((\d+)U?\)')
    pos_matches = pos_pattern.findall(intermediary_holding_place)

    peripheral_map = collections.defaultdict(dict)
    # Track assigned bits per register to prevent overlapping alias duplicates
    assigned_bits_tracker = collections.defaultdict(set)

    for full_macro, reg_name, field_name, pos_str in pos_matches:
        pos = int(pos_str)
        
        # Pull matching mask configuration
        mask_match = re.search(rf'#define\s+{full_macro}_Msk\s+\((0x[0-9A-Fa-f]+)U?', intermediary_holding_place)
        if mask_match:
            mask_val = int(mask_match.group(1), 16)
            
            # BULLETPROOF FIX 1: Safely un-shift masks that are defined as hardcoded shifted values
            if mask_val > 0xFF: 
                unshifted_mask = mask_val >> pos
            else:
                unshifted_mask = mask_val
                
            width = bin(unshifted_mask).count('1') if unshifted_mask != 0 else 1
        else:
            width = 1

        # BULLETPROOF FIX 2: Check for overlapping/alias bits (e.g. ADC12SEL vs ADC1SEL)
        field_bits = set(range(pos, pos + width))
        if field_bits.intersection(assigned_bits_tracker[reg_name]):
            # Skip this field variant; the bits are already mapped under an alternative name
            continue
            
        # Register the bits as locked
        assigned_bits_tracker[reg_name].update(field_bits)
        peripheral_map[reg_name][field_name] = (pos, width)

    # Step 3: Construct Output
    output_lines = [
        f"/* Automatically Generated Bulletproof Bitfield Unions */",
        f"#ifndef {prefix}_BITFIELD_H",
        f"#define {prefix}_BITFIELD_H\n",
        "#include <stdint.h>\n"
    ]

    for reg_name in sorted(peripheral_map.keys()):
        output_lines.append(f"typedef union\n{{")
        output_lines.append(f"    volatile uint32_t reg;\n")
        output_lines.append(f"    struct\n    {{")

        fields = peripheral_map[reg_name]
        sorted_fields = sorted(fields.items(), key=lambda x: x[1][0])

        current_bit = 0
        reserved_count = 0

        for field_name, (pos, width) in sorted_fields:
            if pos > current_bit:
                gap = pos - current_bit
                output_lines.append(f"        volatile uint32_t RESERVED{reserved_count:<2}  : {gap};")
                reserved_count += 1
                current_bit = pos

            if pos == current_bit:
                output_lines.append(f"        volatile uint32_t {field_name:<20} : {width};")
                current_bit += width

        if current_bit < 32:
            output_lines.append(f"        volatile uint32_t RESERVED{reserved_count:<2}  : {32 - current_bit};")

        output_lines.append(f"    }} par;\n")
        output_lines.append(f"}} {prefix}_{reg_name}_TypeDef;\n")

    output_lines.append(f"#endif /* {prefix}_BITFIELDS_H */")
    
    if output_h_path:
        with open(output_h_path, 'w', encoding='utf-8') as f:
            f.write("\n".join(output_lines))
        print(f"Generated bulletproof file: {output_h_path}")
    else:
        print("\n".join(output_lines))

if __name__ == "__main__":
    generate_peripheral_bitfields_bulletproof("stm32g473xx.h", prefix="RCC", output_h_path="rcc_bitfields.h")

