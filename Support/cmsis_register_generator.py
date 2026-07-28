import re
import sys


# ============================================================
# CMSIS Register Generator
# USAGE: python cmsis_register_generator.py stm32g473xx.h
# ============================================================


def get_width(mask):

    value = mask

    count = 0

    while value:

        if value & 1:
            count += 1

        value >>= 1

    return count



def parse_define(filename):

    fields = {}

    with open(filename, "r", encoding="utf-8") as f:

        for line in f:

            # Exemplo:
            # #define I2C_CR1_PE_Pos (0U)

            m = re.match(
                r"#define\s+(\w+)_Pos\s+\((\d+)U?\)",
                line
            )

            if m:

                name = m.group(1)

                pos = int(m.group(2))

                fields.setdefault(name, {})["pos"] = pos


            # Exemplo:
            # #define I2C_CR1_PE_Msk (0x1UL << I2C_CR1_PE_Pos)

            m = re.match(
                r"#define\s+(\w+)_Msk\s+\((0x[0-9A-Fa-f]+)",
                line
            )

            if m:

                name = m.group(1)

                mask = int(m.group(2),16)

                fields.setdefault(name, {})["mask"] = mask


    return fields



def split_field(name):

    #
    # I2C_CR1_PE
    #
    # I2C
    # CR1
    # PE
    #

    p = name.split("_")

    peripheral = p[0]

    register = p[1]

    field = "_".join(p[2:])

    return peripheral, register, field



def generate_registers(fields, output):

    registers = {}


    for name,data in fields.items():

        if "pos" not in data:
            continue

        if "mask" not in data:
            continue


        peripheral, register, field = split_field(name)


        key = peripheral + "_" + register


        if key not in registers:

            registers[key] = []


        registers[key].append(
            (
                field,
                data["pos"],
                get_width(data["mask"])
            )
        )


    with open(output,"w",encoding="utf-8") as f:


        f.write("#ifndef STM32G4_REGISTER_H\n")
        f.write("#define STM32G4_REGISTER_H\n\n")
        f.write("#include <stdint.h>\n\n")


        for reg,items in registers.items():


            items.sort(
                key=lambda x:x[1]
            )


            f.write(
                "typedef union\n{\n"
            )

            f.write(
                "    uint32_t reg;\n\n"
            )


            f.write(
                "    struct\n    {\n"
            )


            bit = 0

            reserved = 0


            for name,pos,width in items:


                if pos > bit:

                    f.write(
                        f"        uint32_t RESERVED{reserved} : {pos-bit};\n"
                    )

                    reserved += 1


                f.write(
                    f"        uint32_t {name} : {width};\n"
                )


                bit = pos + width



            if bit < 32:

                f.write(
                    f"        uint32_t RESERVED{reserved} : {32-bit};\n"
                )


            f.write(
                "    } par;\n\n"
            )

            f.write(
                f"}} {reg}_BitField_TypeDef;\n\n"
            )


        f.write("#endif\n")



# ============================================================
# MAIN
# ============================================================

if __name__ == "__main__":


    cmsis = sys.argv[1]

    output = "stm32g4_register.h"


    data = parse_define(cmsis)

    print("Fields encontrados:", len(data))


    generate_registers(
        data,
        output
    )


    print("Gerado:", output)
    
    
