import matplotlib.pyplot as plt
import csv
import re
import numpy as np

headers=[]
times=[]
memory=[]

with open('./RecuLCSData.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    #  headers = plots[0]
    #  times = plots[1]
    #  memory = plots[2]
    i = 0
    for row in plots:
        for column in row:
            print(column)
            if i == 0:
                m = re.match(r"(\S+)x(\S+)", column)
                print(m.group(1))
                headers.append(int(m.group(1)) + int(m.group(2)))
                #  headers.append(int(m.group(1)))
            if i == 1:
                times.append(int(column)/1000)
            if i == 2:
                memory.append(float(column)/1000)


        i += 1
        #  headers.append(int(m.groups()[0]))
        #  times.append(int(row[1]))
        #  memory.append(int(row[2]))

print(len(headers))
print(headers)
print(len(times))
print(times)
print(len(memory))
print(memory)

fig,ax = plt.subplots()
# make a plot
ax.plot(headers, times, color="red", marker="o")
# set x-axis label
ax.set_xlabel("n + m",fontsize=14)
# set y-axis label
ax.set_ylabel("Time (s)",color="red",fontsize=14)
# twin object for two different y-axis on the sample plot
ax2=ax.twinx()
# make a plot with different y-axis using second axis object
ax2.plot(headers, memory,color="blue",marker="v")
ax2.set_ylabel("Memory (kB)",color="blue",fontsize=14)

ax.title.set_text("Memory usage and time against n + m (Recursive)")


#  plt.plot(headers,times, marker='o')
#  plt.plot(headers,memory, marker='v')

#  plt.title('Time and space (Memoisation)')

#  plt.xlabel('n')
#  plt.ylabel('')

fig.savefig("RecuXnmNEW.jpg")
