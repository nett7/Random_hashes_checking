def main():
    print("Write lenght of password\n")
    PASSWORD_LENGHT = int(input())
    f = open("contents.txt", 'r')
    if f.mode == 'r':
        contents = f.read()
    f.close()

    index = contents.find("result\n----------------------------------------------------------------")
    contents = contents[index:]

    contents_lines = contents.splitlines()
    contents_lines = contents_lines[2:]

    f2 = open("answers.txt", '+w')

    for i in contents_lines:
        i = i[66:66+PASSWORD_LENGHT]
        f2.write(i +'\n')
    f2.close()


if __name__ == '__main__':
    main()
