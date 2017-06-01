import os

__author__ = 'Smallb'


def process_file(path_to_main_folder, filename, num):
    file_name = filename + ".txt"
    result_file_name = "pad_" + file_name
    if os.path.exists(path_to_main_folder + file_name):
        file = open(path_to_main_folder + file_name, 'r')
        result_file = open(path_to_main_folder + result_file_name, 'w')
        pad_file(file, result_file, num)
        file.close()
        result_file.close()
    else:
        print("file not found")


def pad_file(inp, output, num):
    for line in inp:
        if not line.isspace():
            nums = [' '*len(str(x)) for x in range(0, num)]
            nums_from_line = line[0:-2].split(' ')
            for s in nums_from_line:
                nums[int(s)] = s
            for s in nums:
                output.write(s + ' ')
            output.write('\n')


def main():
    path_to_main_folder = os.getcwd()
    path_to_main_folder = path_to_main_folder[0:path_to_main_folder.rfind('\\Scripts') + 1]
    for num in [34]:
        process_file(path_to_main_folder, "BooleanAutomat" + str(num), num)

main()