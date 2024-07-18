import chardet

def detect_encoding(file_path):
    with open(file_path, 'rb') as file:
        raw_data = file.read()
    result = chardet.detect(raw_data)
    return result['encoding']

def convert_file_encoding(input_file, source_encoding, target_encoding):
    with open(input_file, 'r', encoding=source_encoding) as f:
        content = f.read()

    with open(input_file, 'w', encoding=target_encoding) as f:
        f.write(content)

file = '4.txt'
source_encoding = detect_encoding(file)
print(f"Определенная кодировка: {source_encoding}")

target_encoding = 'utf-8'
convert_file_encoding(file, source_encoding, target_encoding)
print(f"Файл {file} успешно конвертирован в {target_encoding}")
