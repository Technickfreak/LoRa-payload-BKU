import os
import csv


# with open('source_data\source_table.csv') as csvdatei:
#     csv_reader_object = csv.reader(csvdatei, delimiter=';')
#     for row in csv_reader_object:
#         #print(row[0],"=",row[1],",")
#         txt = "{0} = {1},"
#         print(txt.format(*row))


# f = open("demofile.txt", "r")
# print(f.read())


import sys,os

scriptPath, _ = os.path.split(os.path.abspath(__file__))
source_folder_name = "source_code"
source_code_folder = os.path.join(scriptPath, source_folder_name)
source_table = os.path.join(scriptPath, "source_table.csv")
#target_code_folder = os.path.join(scriptPath,"..")
temp = scriptPath.split("\\")
source_folders_names = os.path.join(temp[len(temp)-1],source_folder_name)
print(source_table)

#print(source_table.replace(source_main_folder_name+"\\", ""))

for path, subdirs, files in os.walk(source_code_folder):
    for name in files:
        source_path = os.path.join(path, name)
        target_file = open(source_path.replace(source_folders_names+"\\", ""), "a")
        print(source_path)
        source_file = open(source_path, "r")
        for line in source_file:
            target_file.write(line)
            if line.find("Python-Marker") != -1:
                x = line.split("#")
                form =(x[len(x)-1])
                with open(source_table) as csvdatei:
                    csv_reader_object = csv.reader(csvdatei, delimiter=';')
                    for row in csv_reader_object:
                        if row[0] == "true":
                            target_file.write(form.format(*row))
        target_file.close()
                
        