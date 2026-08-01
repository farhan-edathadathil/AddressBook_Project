#include<stdio.h>
int main()
{
    int choice,cb=0,m=0,am=0,cs=0,t=0,total=0;
    printf("---------WELCOME TO--------\n");
    printf("------MALABAR KITCHEN------\n\n");
    do
    {
        printf("\n----HERE IS OUR MENU----\n\n");
        printf("1 - CHICKEN BIRIYANI  - 140 rs\n2 - MALABAR MEALS     - 90 rs\n3 - ALFAHAM MANDHI    - 240 rs\n4 - CHICKEN SHAWAYA   - 240 rs\n5 - TEA               - 12 rs\n6 - EXIT AND PAY\n\n");
        printf("Enter the number of what you want :");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            printf("\nChicken Biriyani added to your cart\n");
            cb++;
            break;

            case 2:
            printf("\nMalabar meals added to your cart\n");
            m++;
            break;

            case 3:
            printf("\nAlfaham mandhi added to your cart\n");
            am++;
            break;

            case 4:
            printf("\nChicken shawaya added to your cart\n");
            cs++;
            break;

            case 5:
            printf("\nTea added to your cart\n");
            t++;
            break;

            default:
            goto exit;
        }
        total = cb*140 + m*90 + am*240 + cs*240 + t*12;
        printf("\n\n----------*******--------\n");
        printf("\n\n----Your current cart items----\n\n");
        if(cb)
            printf("Chicken biriyani  * %d\n",cb);
        if(m)
            printf("Malabar meals     * %d\n",m);
        if(am)
            printf("Alfaham mandhi    * %d\n",am);
        if(cs)
            printf("Chicken shawaya   * %d\n",cs);
        if(t)
            printf("Tea               * %d\n",t);
        printf("\nYour current cart value (including GST) = %g\n",total+(total*0.18));
        exit:
        printf("\n\n---------*********---------\n");
    } while (choice>0 && choice<6);

    printf("\n\n-----YOUR BILL------\n\n");
    if(cb)
        printf("Chicken biriyani  - 140 rs * %d\n",cb);
    if(m)
        printf("Malabar meals     - 90 rs * %d\n",m);
    if(am)
        printf("Alfaham mandhi    - 240 rs* %d\n",am);
    if(cs)
        printf("Chicken shawaya   - 240 rs* %d\n",cs);
    if(t)
        printf("Tea               - 12 * %d\n",t);
    printf("\nYour total bill amount         = %d rs\n",total);
    printf("\nYour bill amount including GST = %g rs\n",total+(total*0.18));
    printf("\n\n-----Thank You Visit Again-----\n");
    printf("\n\n---------*******----------\n");

}