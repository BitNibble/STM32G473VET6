import math
from PIL import Image, ImageDraw, ImageFont

def generate_font_array(font_path, size, output_filename, font_name_override=None):
    """
    Generates a C-style font array matching an arbitrary NxN grid (multiples of 8).
    All characters are tightly left-justified (anchored horizontally at index 0).
    """
    if size % 8 != 0:
        raise ValueError("Size must be a multiple of 8 (e.g., 8, 16, 24, 32...)")
        
    # Configuration
    first = 32
    last = 126
    glyph_w = size
    glyph_h = size
    
    # Calculate bytes per row needed
    bytes_per_row = size // 8
    
    # Choose font size dynamically to fit nicely within the bounding box
    font_pt_size = int(size * 0.95) if size > 8 else size
    font = ImageFont.truetype(font_path, font_pt_size)
    
    # Internal function to render a single character
    def render_char(c):
        img = Image.new("1", (glyph_w, glyph_h), 0)
        d = ImageDraw.Draw(img)
        
        # Calculate bounding box for vertical alignment
        bbox = font.getbbox(c)
        if bbox:
            char_h = bbox[3] - bbox[1]
            
            # FIX: Force strict left-justification (X = 0) by counter-shifting the font's internal offset
            x_shift = -bbox[0] 
            
            # Keep vertical centering so loops/descenders do not clip
            y_shift = max(0, (glyph_h - char_h) // 2) - bbox[1]
        else:
            x_shift, y_shift = 0, 0
            
        # Render the character left-justified
        d.text((x_shift, y_shift), c, 1, font=font)
        
        rows = []
        for y in range(glyph_h):
            row = 0
            for x in range(glyph_w):
                row = (row << 1) | img.getpixel((x, y))
            rows.append(row)
        return rows

    # Write array code to file
    array_name = font_name_override or f"font{size}x{size}"
    with open(output_filename, "w") as f:
        f.write(f"// Generated {size}x{size} font grid ({bytes_per_row} bytes per row) - Left Justified\n")
        f.write(f"const uint8_t {array_name}[] PROGMEM = {{\n")
        
        for c in range(first, last + 1):
            rows = render_char(chr(c))
            f.write(f"\n    // '{chr(c)}' 0x{c:02x}\n    ")
            
            for r in rows:
                # Shift and extract the bytes in Big-Endian order matching your C function sequence
                for b_idx in reversed(range(bytes_per_row)):
                    byte_val = (r >> (b_idx * 8)) & 0xff
                    f.write(f"0x{byte_val:02x}, ")
            f.write("\n")
            
        f.write("};\n")
    print(f"Successfully generated: {output_filename} ({size}x{size})")

# ==========================================
# USAGE EXAMPLES
# ==========================================
FONT_FILE = "dejavusansmono.ttf"

# Call this function to generate your left-justified files:
generate_font_array(FONT_FILE, size=8, output_filename="font8x8.txt")
generate_font_array(FONT_FILE, size=16, output_filename="font16x16.txt")
generate_font_array(FONT_FILE, size=24, output_filename="font24x24.txt")
generate_font_array(FONT_FILE, size=32, output_filename="font32x32.txt")
