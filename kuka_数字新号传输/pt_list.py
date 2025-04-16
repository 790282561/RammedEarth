f_path = "pt_time"

with open(f_path, 'r') as f:
    pt_list = f.readlines()
for i in range(len(pt_list)):
    pt_list[i] = pt_list[i].rstrip('\n')

num_list = []
for j in range(0, len(pt_list), 4):
    temp_list = []
    temp_list.append(float(pt_list[j])*1000)
    temp_list.append(float(pt_list[j+1])*1000)
    temp_list.append(float(pt_list[j+2])*1000)
    # temp_list.append(float(pt_list[j+3]))
    num_list.append(temp_list)
str_pt = str(num_list)
str_pt = str_pt.replace('[', '{')
str_pt = str_pt.replace(']', '}')
print(str_pt)
