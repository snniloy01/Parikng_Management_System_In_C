#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car
{
    int id;
    char brand[50];
    char model[50];
    char plateNumber[20];
    char ownerName[50];
    char ownerPhoneNumber[15];
};

struct Node
{
    struct Car data;
    struct Node* next;
};

struct CarQueue
{
    struct Node* front;
    struct Node* rear;
};

void initCarQueue(struct CarQueue* carQueue)
{
    carQueue->front = NULL;
    carQueue->rear = NULL;
}

int isEmpty(struct CarQueue* carQueue)
{
    return carQueue->front == NULL;
}

void enqueue(struct CarQueue* carQueue, const struct Car* newCar)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = *newCar;
    newNode->next = NULL;

    if (isEmpty(carQueue))
    {
        carQueue->front = newNode;
        carQueue->rear = newNode;
    }
    else
    {
        carQueue->rear->next = newNode;
        carQueue->rear = newNode;
    }
}

struct Car dequeue(struct CarQueue* carQueue)
{
    if (isEmpty(carQueue))
    {
        fprintf(stderr, "Queue Empty...\n");
        exit(EXIT_FAILURE);
    }

    struct Node* temp = carQueue->front;
    struct Car car = temp->data;

    if (carQueue->front == carQueue->rear)
    {
        carQueue->front = carQueue->rear = NULL;
    }
    else
    {
        carQueue->front = carQueue->front->next;
    }

    free(temp);
    return car;
}

struct ParkingSpot
{
    struct Car data;
    int occupied;
};

struct ParkingLot
{
    struct ParkingSpot spots[100];
};

void initParkingLot(struct ParkingLot* parkingLot)
{
    for (int i = 0; i < 100; ++i)
    {
        parkingLot->spots[i].occupied = 0;
    }
}

void parkCar(struct ParkingLot* parkingLot, const struct Car* newCar)
{
    for (int i = 0; i < 100; ++i)
    {
        if (!parkingLot->spots[i].occupied)
        {
            parkingLot->spots[i].data = *newCar;
            parkingLot->spots[i].occupied = 1;
            printf("Your car parked successfully in spot %d\n", i + 1);
            return;
        }
    }
    printf("Parking lot is full...\n");
}

void removeCar(struct ParkingLot* parkingLot, const char* plateNumber)
{
    for (int i = 0; i < 100; ++i)
    {
        if (parkingLot->spots[i].occupied && strcmp(parkingLot->spots[i].data.plateNumber, plateNumber) == 0)
        {
            printf("Removing car from spot %d: %s %s (Plate: %s)\n", i + 1, parkingLot->spots[i].data.brand, parkingLot->spots[i].data.model, parkingLot->spots[i].data.plateNumber);
            parkingLot->spots[i].occupied = 0;
            return;
        }
    }
    printf("Car with plate number %s not found in the parking lot...\n", plateNumber);
}

void displayParkingLot(struct ParkingLot* parkingLot)
{
    printf("Parking Lot Status:\n");
    for (int i = 0; i < 100; ++i)
    {
        printf("Spot %d: ", i + 1);
        if (parkingLot->spots[i].occupied)
        {
            printf("Occupied - %s %s (Plate: %s, Owner: %s, Phone: %s)\n",
                   parkingLot->spots[i].data.brand,
                   parkingLot->spots[i].data.model,
                   parkingLot->spots[i].data.plateNumber,
                   parkingLot->spots[i].data.ownerName,
                   parkingLot->spots[i].data.ownerPhoneNumber);
        }
        else
        {
            printf("Empty...\n");
        }
    }
}


void addCar(struct Car parkingLot[], int* size, struct CarQueue* carQueue, struct ParkingLot* parkingLotObj)
{
    if (*size < 100)
    {
        printf("\nEnter Car Brand   : ");
        fflush(stdin);
        fgets(parkingLot[*size].brand, sizeof(parkingLot[*size].brand), stdin);
        parkingLot[*size].brand[strcspn(parkingLot[*size].brand, "\n")] = '\0';

        printf("Enter Car Model   : ");
        fgets(parkingLot[*size].model, sizeof(parkingLot[*size].model), stdin);
        parkingLot[*size].model[strcspn(parkingLot[*size].model, "\n")] = '\0';

        printf("Enter Plate Number: ");
        fgets(parkingLot[*size].plateNumber, sizeof(parkingLot[*size].plateNumber), stdin);
        parkingLot[*size].plateNumber[strcspn(parkingLot[*size].plateNumber, "\n")] = '\0';

        printf("Enter Owner Name  : ");
        fgets(parkingLot[*size].ownerName, sizeof(parkingLot[*size].ownerName), stdin);
        parkingLot[*size].ownerName[strcspn(parkingLot[*size].ownerName, "\n")] = '\0';

        printf("Enter Owner Phone : ");
        fgets(parkingLot[*size].ownerPhoneNumber, sizeof(parkingLot[*size].ownerPhoneNumber), stdin);
        parkingLot[*size].ownerPhoneNumber[strcspn(parkingLot[*size].ownerPhoneNumber, "\n")] = '\0';

        parkingLot[*size].id = *size + 1;
        (*size)++;
        printf("Car parked successfully!\n");
        enqueue(carQueue, &parkingLot[*size - 1]);
        parkCar(parkingLotObj, &parkingLot[*size - 1]);
    }
    else
    {
        printf("Parking lot is full...\n");
    }
}
void searchCar(struct Car parkingLot[], int size, const char* plateNumber)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(parkingLot[i].plateNumber, plateNumber) == 0)
        {
            printf("Car found in Parking Lot:\n");
            printf("Brand       : %s\n", parkingLot[i].brand);
            printf("Model       : %s\n", parkingLot[i].model);
            printf("Plate Number: %s\n", parkingLot[i].plateNumber);
            return;
        }
    }
    printf("%s not found in Parking Lot...\n", plateNumber);
}

int main()
{
    struct Car parkingLot[100];
    int size = 0;
    int choice;
    char searchPlateNumber[20];
    struct CarQueue carQueue;
    struct ParkingLot parkingLotObj;

    initCarQueue(&carQueue);
    initParkingLot(&parkingLotObj);

    do
    {
        printf("\n===Car Parking System===\n");
        printf("1. Park a Car\n");
        printf("2. Display Parking Lot\n");
        printf("3. Search Car\n");
        printf("4. Remove Car\n");
        printf("5. Add Another Car in free Lot\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addCar(parkingLot, &size, &carQueue, &parkingLotObj);
            break;
        case 2:
            displayParkingLot(&parkingLotObj);
            break;
        case 3:
            printf("\nEnter the plate number to search: ");
            fflush(stdin);
            fgets(searchPlateNumber, sizeof(searchPlateNumber), stdin);
            searchPlateNumber[strcspn(searchPlateNumber, "\n")] = '\0';
            searchCar(parkingLot, size, searchPlateNumber);
            break;
        case 4:
            printf("\nEnter the plate number to remove: ");
            fflush(stdin);
            fgets(searchPlateNumber, sizeof(searchPlateNumber), stdin);
            searchPlateNumber[strcspn(searchPlateNumber, "\n")] = '\0';
            removeCar(&parkingLotObj, searchPlateNumber);
            break;
        case 5:
            addCar(parkingLot, &size, &carQueue, &parkingLotObj);
            break;
        case 0:
            printf("Thank You!\n");
            break;
        default:
            printf("Invalid choice...\n");
        }
    }
    while (choice != 0);
    return 0;
}
