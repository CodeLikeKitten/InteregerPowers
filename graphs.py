import matplotlib.pyplot as plt
    
powTimes = list(map(float, open("powTimes.txt", "r").read().split('\n')))
binaryTimes = list(map(float, open("binaryTimes.txt", "r").read().split('\n')))
preCalcTimes = list(map(float, open("preCalcTimes.txt", "r").read().split('\n')))
hardcodePowTimes = list(map(float, open("hardcodePowTimes.txt", "r").read().split('\n')))

differencesBinary = []

for i in range(len(powTimes)):
    differencesBinary.append(powTimes[i] / binaryTimes[i])

differencesPrecalc = []

for i in range(len(powTimes)):
    differencesPrecalc.append(powTimes[i] / preCalcTimes[i])

differencesHardcode = []

for i in range(len(powTimes)):
    differencesHardcode.append(powTimes[i] / hardcodePowTimes[i])    

figure, axis = plt.subplots(2, 2)

t = range(0, len(powTimes))

axis[0, 0].plot(t, powTimes)
axis[0, 0].plot(t, binaryTimes)
axis[0, 0].plot(t, preCalcTimes)
axis[0, 0].plot(t, hardcodePowTimes)
axis[0, 0].set_title("Execution times mcs")
axis[0, 0].legend(["cmath pow", "binary pow", "precalc", "hardcoded pow"])

axis[0, 1].plot(t, differencesBinary)
axis[0, 1].set_title("Time difference binary")

axis[1, 0].plot(t, differencesPrecalc)
axis[1, 0].set_title("Time difference precalc")

axis[1, 1].plot(t, differencesHardcode)
axis[1, 1].set_title("Time difference hardcode")

# Combine all the operations and display
plt.show()