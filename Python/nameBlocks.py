name = "Philip Bell" #setes the verable name to my name
incrementor = 2 #sets how many letter to print on each line
for i in range(0,len(name),incrementor): #loops through the following 
        try: #tries to do the following
            print name[i] + name[i+1] #prints out the current value in the list and the next one
        except IndexError: #if it runs off the end of the array and causes a IndexError then it does the following
            print name[i] #print the current value in the array
            