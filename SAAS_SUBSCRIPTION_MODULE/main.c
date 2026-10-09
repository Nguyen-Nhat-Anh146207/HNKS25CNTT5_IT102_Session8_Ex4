
#include <stdio.h>

struct Subscription {
    int user_id;
    char account_name[31];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
};

int main() {
    struct Subscription accounts[50];
    int N;
    int i;

    int downgraded_count = 0;
    int violation_count = 0;

    printf("============================================\n");
    printf("       STREAMFLIX SUBSCRIPTION AUDITOR\n");
    printf("============================================\n");

    // BƯOC 1: NHAP SO LUONG TAI KHOAN
    do {
        printf("Nhap so luong tai khoan (1-50): ");
        if (scanf("%d", &N) != 1) {
            printf("Du lieu khong hop le!\n");
            return 1;
        }

        if (N < 1 || N > 50) {
            printf("Vui long nhap N tu 1 den 50!\n");
        }
    } while (N < 1 || N > 50);
    for (i = 0; i < N; i++) {
        printf("\n--- Tai khoan %d ---\n", i + 1);

        printf("Nhap user_id: ");
        scanf("%d", &accounts[i].user_id);

        printf("Nhap account_name (email, toi da 30 ky tu): ");
        scanf("%30s", accounts[i].account_name);

        do {
            printf("Nhap plan_type (1-Free, 2-Individual, 3-Family): ");
            scanf("%d", &accounts[i].plan_type);

            if (accounts[i].plan_type < 1 || accounts[i].plan_type > 3) {
                printf("Loai goi khong hop le! Nhap lai.\n");
            }
        } while (accounts[i].plan_type < 1 || accounts[i].plan_type > 3);

        do {
            printf("Nhap so thiet bi dang dung: ");
            scanf("%d", &accounts[i].active_devices);

            if (accounts[i].active_devices < 0) {
                printf("So thiet bi khong duoc am!\n");
            }
        } while (accounts[i].active_devices < 0);

        do {
            printf("Nhap so ngay no cuoc: ");
            scanf("%d", &accounts[i].days_overdue);

            if (accounts[i].days_overdue < 0) {
                printf("So ngay no khong duoc am!\n");
            }
        } while (accounts[i].days_overdue < 0);

        accounts[i].account_status = 1;
    }

    for (i = 0; i < N; i++) {

        if (accounts[i].plan_type == 1) {
            accounts[i].max_devices = 1;
        } else if (accounts[i].plan_type == 2) {
            accounts[i].max_devices = 1;
        } else {
            accounts[i].max_devices = 5;
        }

        if (accounts[i].days_overdue > 3 &&
            accounts[i].plan_type != 1) {

            accounts[i].plan_type = 1;
            accounts[i].max_devices = 1;
            accounts[i].account_status = 0;

            downgraded_count++;
        }

        if (accounts[i].active_devices > accounts[i].max_devices) {
            violation_count++;
        }
    }

    printf("\n\n");
    printf("===============================================================\n");
    printf("             BAO CAO KIEM TOAN STREAMFLIX\n");
    printf("===============================================================\n");

    printf("%-8s %-22s %-12s %-10s %-10s %-8s %-13s\n",
           "User ID", "Account Name", "Goi dich vu",
           "Thiet bi", "Toi da", "No ngay", "Trang thai");

    printf("----------------------------------------------------------------");

    for (i = 0; i < N; i++) {
        char plan_name[15];
        char status_name[15];

        if (accounts[i].plan_type == 1) {
            sprintf(plan_name, "Free");
        } else if (accounts[i].plan_type == 2) {
            sprintf(plan_name, "Individual");
        } else {
            sprintf(plan_name, "Family");
        }

        if (accounts[i].account_status == 1) {
            sprintf(status_name, "Active");
        } else {
            sprintf(status_name, "Downgraded");
        }

        printf("%-8d %-22s %-12s %-10d %-10d %-8d %-13s\n", accounts[i].user_id, accounts[i].account_name, plan_name, accounts[i].active_devices, accounts[i].max_devices, accounts[i].days_overdue, status_name);
    }

    printf("\n===============================================================\n");
    printf("              THONG KE VAN HANH\n");
    printf("===============================================================\n");
    printf("Tong so tai khoan da ra soat: %d\n", N);
    printf("So tai khoan bi ha cap ve Free do no cuoc: %d\n", downgraded_count);
    printf("So tai khoan vi pham gioi han thiet bi: %d\n", violation_count);
    printf("===============================================================\n");

    return 0;
}