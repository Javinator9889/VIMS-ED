from ast import arg
from operator import ge
import sys
import requests
from bs4 import BeautifulSoup


def main(args):
    if len(args) != 2:
        print(f"Usage: {__file__} URL OUTPUT")
        return 1

    url = args[0]
    output = args[1]
    data = requests.get(
        url,
        headers={
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36"
        },
    )
    content = BeautifulSoup(data.text, features="lxml")
    all_codes = content.find("div", attrs={"class": "main"}).find("ul")
    generated_c_desc = ["#ifdef __AVR__\n", "#include <avr/pgmspace.h>\n", "#else\n", "#define PROGMEM\n", "#endif\n\n"]
    generated_c_map = ["const char *DTC_MAPPER[] PROGMEM = {\n"]
    trans = str.maketrans({'"': r"\"", "\n": " ", "\r": " ", "\t": " "})
    for code in all_codes.findChildren("li"):
        line = code.get_text().strip()
        dtc = line[:5]
        explanation = line[5:].strip().translate(trans)
        generated_c_desc.append(f'const char {dtc}[] PROGMEM = "{explanation}";\n')
        generated_c_map.append(f"  {dtc},\n")
    generated_c_desc.append("\n")
    generated_c_map.append("};\n")
    
    with open(output, "w") as c:
        c.writelines(generated_c_desc)
        c.writelines(generated_c_map)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
