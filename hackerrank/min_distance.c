#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

int icmp ( const void * aa, const void * bb ) {
    int a = *(((int*)aa));
    int b = *(((int*)bb));

    return a-b;
}
// Complete the minimumDistances function below.
int minimumDistances(int a_count, int* a) {
}

#if 0
500
20 760 143 550 365 559 539 299 160 955 706 462 329 786 989 867 47 648 171 369 625 975 538 532 973 25 515 395 724 487 618 745 247 113 647 612 24 186 263 537 493 321 999 174 108 988 394 507 988 917 228 613 892 118 497 218 144 13 613 220 500 583 965 748 49 613 712 73 151 976 610 997 297 961 171 757 949 565 616 937 483 844 903 727 963 400 945 459 765 910 31 266 494 997 366 895 962 78 968 465 406 931 814 56 892 338 813 194 255 782 483 90 626 386 818 941 139 115 752 904 26 784 522 872 133 888 767 447 967 87 264 725 370 79 781 263 417 947 809 672 729 292 763 355 31 933 649 522 48 401 426 426 537 301 650 670 189 769 469 508 857 734 234 227 813 15 842 582 314 651 606 43 296 721 751 679 654 400 201 55 153 979 481 691 280 484 713 470 253 183 978 462 269 564 690 434 580 884 16 894 536 622 290 184 696 41 863 350 441 64 757 946 395 239 989 676 75 703 498 328 238 828 791 507 393 833 941 325 717 309 571 605 283 861 141 979 902 4 682 695 420 439 642 816 30 631 844 105 686 342 786 276 170 577 135 915 762 428 240 831 737 812 437 373 673 930 352 928 935 34 623 707 826 617 523 856 601 719 314 287 413 100 916 584 677 51 499 791 480 92 622 569 904 411 942 577 342 647 857 629 33 481 336 859 450 212 716 51 931 30 691 345 130 607 281 159 10 132 302 490 224 924 60 480 336 354 410 30 1 267 659 35 100 347 894 551 911 962 602 195 344 293 892 474 252 173 985 263 657 639 105 234 564 165 714 252 872 124 634 873 744 293 908 844 992 803 395 904 765 998 99 462 643 991 936 248 516 274 863 525 913 968 759 829 486 826 81 358 302 67 231 46 360 140 891 705 295 286 609 412 636 60 874 632 403 163 232 919 789 95 796 54 63 556 884 901 734 317 259 36 385 491 83 97 983 326 154 630 964 763 42 953 175 269 585 578 432 817 849 573 264 998 627 327 906 511 229 640 181 840 676 918 683 111 15 666 789 170 648 754 285 43 707 813 312 644 743 96 813 945 669 77 943 296 404 849 160 985 489 693 826 517 611 509 981 978 528 770 148 528 524 786 571 583 951 883 227 694 979 40

1 expected distance

#endif
int main() {
}


#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** a_temp = split_string(readline());

    int* a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* a_item_endptr;
        char* a_item_str = *(a_temp + i);
        int a_item = strtol(a_item_str, &a_item_endptr, 10);

        if (a_item_endptr == a_item_str || *a_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(a + i) = a_item;
    }

    int a_count = n;

    int result = minimumDistances(a_count, a);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
#endif
