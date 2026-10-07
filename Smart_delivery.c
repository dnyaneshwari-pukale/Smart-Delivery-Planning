#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    float value;
    float weight;
    float ratio;
    float selected;
} Package;

Package packages[MAX];
int n = 0;
float capacity = 0;
int detailsEntered = 0;
int ratioCalculated = 0;
int sorted = 0;
int resultCalculated = 0;

/* Function to calculate Value/Weight ratio */
void calculateRatio() {
    int i;

    if (!detailsEntered) {
        printf("\nPlease enter package details first.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        if (packages[i].weight > 0)
            packages[i].ratio =
                packages[i].value / packages[i].weight;
        else
            packages[i].ratio = 0;
    }

    ratioCalculated = 1;
    sorted = 0;
    resultCalculated = 0;

    printf("\nValue/Weight ratios calculated successfully.\n");
}

/* Function to sort packages by decreasing ratio */
void sortPackages() {
    int i, j;
    Package temp;

    if (!ratioCalculated) {
        printf("\nPlease calculate the ratios first.\n");
        return;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {

            if (packages[j].ratio < packages[j + 1].ratio) {
                temp = packages[j];
                packages[j] = packages[j + 1];
                packages[j + 1] = temp;
            }
        }
    }

    sorted = 1;
    resultCalculated = 0;

    printf("\nPackages sorted by decreasing Value/Weight ratio.\n");
}

/* Function to enter package details */
void enterPackageDetails() {
    int i;

    printf("\nEnter number of packages: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of packages.\n");
        n = 0;
        return;
    }

    for (i = 0; i < n; i++) {
        packages[i].id = i + 1;

        printf("\nPackage %d\n", i + 1);

        printf("Enter value/profit: ");
        scanf("%f", &packages[i].value);

        printf("Enter weight: ");
        scanf("%f", &packages[i].weight);

        packages[i].ratio = 0;
        packages[i].selected = 0;
    }

    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);

    detailsEntered = 1;
    ratioCalculated = 0;
    sorted = 0;
    resultCalculated = 0;

    printf("\nPackage details entered successfully.\n");
}

/* Function to display package details */
void displayPackageDetails() {
    int i;

    if (!detailsEntered) {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\n-----------------------------------------------------\n");
    printf("ID\tValue\tWeight\tRatio\n");
    printf("-----------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               packages[i].id,
               packages[i].value,
               packages[i].weight,
               packages[i].ratio);
    }

    printf("-----------------------------------------------------\n");
    printf("Vehicle Capacity: %.2f\n", capacity);
}

/* Function to find maximum value */
void findMaximumValue() {
    float remainingCapacity;
    float totalValue = 0;
    float totalWeight = 0;
    int i;

    if (!sorted) {
        printf("\nPlease calculate ratios and sort packages first.\n");
        return;
    }

    remainingCapacity = capacity;

    for (i = 0; i < n; i++) {
        packages[i].selected = 0;

        if (remainingCapacity <= 0)
            break;

        if (packages[i].weight <= remainingCapacity) {

            /* Select complete package */
            packages[i].selected = 1;

            remainingCapacity -= packages[i].weight;
            totalWeight += packages[i].weight;
            totalValue += packages[i].value;

        } else {

            /* Select fraction of package */
            packages[i].selected =
                remainingCapacity / packages[i].weight;

            totalWeight += remainingCapacity;

            totalValue +=
                packages[i].ratio * remainingCapacity;

            remainingCapacity = 0;
        }
    }

    printf("\nMaximum value calculated successfully.\n");

    printf("\nTotal Weight Used : %.2f", totalWeight);
    printf("\nMaximum Value     : %.2f\n", totalValue);

    resultCalculated = 1;
}

/* Function to display selected packages */
void displaySelectedPackages() {
    int i;

    if (!resultCalculated) {
        printf("\nPlease find maximum value first.\n");
        return;
    }

    printf("\n-----------------------------------------------------\n");
    printf("Selected Package Details\n");
    printf("-----------------------------------------------------\n");

    printf("ID\tRatio\tSelected Quantity\tStatus\n");
    printf("-----------------------------------------------------\n");

    for (i = 0; i < n; i++) {

        if (packages[i].selected > 0) {

            printf("%d\t%.2f\t%.2f\t\t",
                   packages[i].id,
                   packages[i].ratio,
                   packages[i].selected);

            if (packages[i].selected == 1)
                printf("Complete\n");
            else
                printf("Fraction\n");
        }
    }

    printf("-----------------------------------------------------\n");
}

/* Main function */
int main() {

    int choice;

    do {
        printf("\n\n==============================================");
        printf("\n SMART DELIVERY PLANNING");
        printf("\n Fractional Knapsack - Greedy Algorithm");
        printf("\n==============================================");

        printf("\n1. Enter Package Details");
        printf("\n2. Display Package Details");
        printf("\n3. Calculate Value/Weight Ratio");
        printf("\n4. Sort Packages by Ratio");
        printf("\n5. Find Maximum Value");
        printf("\n6. Display Selected Packages");
        printf("\n7. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                enterPackageDetails();
                break;

            case 2:
                displayPackageDetails();
                break;

            case 3:
                calculateRatio();
                break;

            case 4:
                sortPackages();
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelectedPackages();
                break;

            case 7:
                printf("\nThank you for using Smart Delivery Planning.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}