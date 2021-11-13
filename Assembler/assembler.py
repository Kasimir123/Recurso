from os import putenv
import sys

if len(sys.argv) != 3:
    print("Usage: assembler.py <assebly-file> <output-file>")
    exit()

asm = open(sys.argv[1], "r").read()
recc = open(sys.argv[2], "wb")

labels = {}
output = b''
to_fix = []

commands = {
    "ISUB"      : b'\x01',
    "IMUL"      : b'\x02',
    "IADD"      : b'\x03', 
    "FADD"      : b'\x04',
    "FSUB"      : b'\x05',
    "ITOF"      : b'\x06',
    "CCONST"    : b'\x07',
    "ICONST"    : b'\x08',
    "SCONST"    : b'\x09',
    "FCONST"    : b'\x0A',
    "STORE"     : b'\x0B',
    "LOAD"      : b'\x0C',
    "HALT"      : b'\x0D',
    "RET"       : b'\x0E',
    "PRINT"     : b'\x0F',
    "POP"       : b'\x10',
    "FUNC"      : b'\x11',
    "FUNCINFO"  : b'\x12',
    "IDIV"      : b'\x13',
    "FDIV"      : b'\x14',
    "CALL"      : b'\x15',
    "INPUT"     : b'\x16',
    "CMP"       : b'\x17',
    "OR"        : b'\x18',
    "AND"       : b'\x19',
    "XOR"       : b'\x1A',
    "NCMP"      : b'\x1B',
    "LTCMP"     : b'\x1C',
    "GTCMP"     : b'\x1D',
    "JMP"       : b'\x1E',
    "IJMP"      : b'\x1F',
    "INC"       : b'\x20',
    "DEC"       : b'\x21',
    "MOV"       : b'\x22',
    "MEMP"      : b'\x23',
    "CMPJMP"    : b'\x24'
}

def parseLine(line):
    global output 
    global labels
    global to_fix

    line = line.strip()

    if ':' in line:
        labels[line.replace(':', " ").strip().upper()] = len(output)
    else:
        command = line.split(' ')[0].upper()

        output += commands[command]

        if command == "LOAD":
            output += int(line.split(' ')[1]).to_bytes(4, 'big')
        elif command == "STORE":
            output += int(line.split(' ')[1]).to_bytes(4, 'big')
        elif command == "CALL":
            output += int(line.split(' ')[1]).to_bytes(4, 'big')
        elif command == "INC":
            output += int(line.split(' ')[1]).to_bytes(4, 'big')
        elif command == "DEC":
            output += int(line.split(' ')[1]).to_bytes(4, 'big')
        elif command == "MEMP":
            output += int(line.split(' ')[1]).to_bytes(4, 'big')
        elif command == "JMP" or command == "CMPJMP":
            if line.split(' ')[1].upper() in labels:
                output += int(labels[line.split(' ')[1].upper()]).to_bytes(4, 'big')
            else:
                to_fix.append((line.split(' ')[1].upper(), len(output)))
                output += int(0).to_bytes(4, 'big')
        elif command == "ICONST":
            output += int(line.split(' ')[1]).to_bytes(8, 'big')

def createHeader():
    output = b''
    output += int(14).to_bytes(4, 'little')
    output += b'\x11\x6d\x61\x69\x6e\x12'
    output += int(2).to_bytes(4, 'big')
    output += int(0).to_bytes(4, 'big')

    return output


for line in asm.split("\n"):
    if len(line.strip()) > 0:
        parseLine(line)

for i in to_fix:
    output = output[:i[1]] + int(labels[i[0]]).to_bytes(4, 'big') + output[i[1] + 4:]

recc.write(createHeader())
recc.write(output)