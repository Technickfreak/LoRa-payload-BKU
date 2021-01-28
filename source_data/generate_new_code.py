import os
import csv
import sys,os

scriptPath, _ = os.path.split(os.path.abspath(__file__))
source_folder_name = "source_code"
source_code_folder = os.path.join(scriptPath, source_folder_name)
source_table = os.path.join(scriptPath, "source_table.csv")
source_table_temp = os.path.join(scriptPath, "source_table_temp.csv")
#target_code_folder = os.path.join(scriptPath,"..")
temp = scriptPath.split("\\")
source_folders_names = os.path.join(temp[len(temp)-1],source_folder_name)+"\\"
print(source_table)

#print(source_table.replace(source_main_folder_name+"\\", ""))
test = open(source_table, "r")
table = test.read().replace("\t", "")
f = open(source_table_temp, "x")
f.write(table)
f.close()

for path, subdirs, files in os.walk(source_code_folder):
    for name in files:
        source_path = os.path.join(path, name)
        print(source_path)
        target_path = source_path.replace(source_folders_names, "")
        if os.path.exists(target_path):
            os.remove(target_path)
        target_file = open(target_path, "a")
        source_file = open(source_path, "r")
        for line in source_file:
            #target_file.write(line)
            if line.find("Python-Marker") != -1:
                x = line.split("#")

                #swith case
                
                form =(x[len(x)-1])
                form = form.replace("\\n", "\n")
                form = form.replace("\\t", "\t")
                with open(source_table_temp) as csvdatei:
                    csv_reader_object = csv.reader(csvdatei, delimiter=';')
                    for row in csv_reader_object:
                        if row[0] == "true":
                            target_file.write(form.format(*row))
                            #target_file.write(line_form.format(*row))
            else:
                target_file.write(line)
        target_file.close()
os.remove(source_table_temp)
                
        