
buildingTest: buildingTest.c buildingPlan.o
	gcc buildingTest.c buildingPlan.o -o buildingTest

buildingPlan.o: buildingPlan.c building.h
	gcc -c buildingPlan.c

clean:
	rm *.o buildingTest