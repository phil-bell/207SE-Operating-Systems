name = "Philip Bell" #setes the verable name to my name
incremtor = 2 #sets how many letter to print on each line
for i in range(0,len(name),incremtor): #loops through the following 
        if i+1<len(name): #if not the end of the list
            print name[i] + name[i+1] #prints out the current value in the list and the next one
        else: #when it is the end of the list
            print name[i] #print the current value in the array
            