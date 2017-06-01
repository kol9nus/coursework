import os


def longest_common_substring(s1, s2):
   m = [[0] * (1 + len(s2)) for i in range(1 + len(s1))]
   longest, x_longest = 0, 0
   for x in range(1, 1 + len(s1)):
       for y in range(1, 1 + len(s2)):
           if s1[x - 1] == s2[y - 1]:
               m[x][y] = m[x - 1][y - 1] + 1
               if m[x][y] > longest:
                   longest = m[x][y]
                   x_longest = x
           else:
               m[x][y] = 0
   return s1[x_longest - longest: x_longest]


def read_strings(filename):
    currentPath = os.getcwd()
    currentPath = currentPath[0:currentPath.rfind('\\') + 1]
    lines = []
    if os.path.exists(currentPath + filename):
        file = open(currentPath + filename, 'r')
        for line in file:
            lines.append(line)

    return lines


strings = read_strings("SyncWordsFor11744....txt")
strs = [strings[0], '']
i = 1
while i < len(strings):
    strs[i % 2] = strings[i]
    strs[i % 2] = longest_common_substring(strs[0], strs[1])
    i += 1

print(strs[(i + 1) % 2])