#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct floor
{
    int data;
    struct floor *next;
};

//function to add the lift floor in the linked list.
struct floor *add(struct floor *head, int no_people, int pos)
{
    int go_floor;
    for (int i = 0; i < no_people; i++)
    {
        printf("Person %d - Enter the floor where you would like to go: ",i+1);
        scanf("%d", &go_floor);
        if (pos != go_floor)
        {
            struct floor *new_node = (struct floor *)malloc(sizeof(struct floor));
            new_node->data = go_floor;
            new_node->next = NULL;
            if (head == NULL)
            {
                head = new_node;
            }
            else
            {
                struct floor *temp1 = head;
                int count = 0;
                while (temp1->next != NULL)
                {
                    temp1 = temp1->next;
                }
                temp1->next = new_node;
            }
        }
        else
        {
            printf("You are already in this floor");
        }
    }
    return head;
}

//This function will remove all the people/floor(multiple also) present in the linked list if lift is at the present floor.
struct floor *remove_people(struct floor *head, int pos)
{
    struct floor *temp = head;
    struct floor *prev = NULL;
    while (temp != NULL)
    {
        if (temp->data == pos)
        {
            if (prev == NULL)
            {
                head = temp->next;
                free(temp);
                temp = head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
    return head;
}

void print_link_list(struct floor *head)
{
    struct floor *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int count_people(struct floor *head)
{
    struct floor *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

//it is used for checking the direction in which the lift will go:
//Initially, if there are more people going up than it will go up and vice-versa
bool fetch_direction(struct floor *head, bool direction, int pos)
{
    struct floor *temp = head;
    bool flag = false;
    if (temp != NULL)
    {
        if (temp->next == NULL)
        {
            if (temp->data > pos)
            {
                direction = true;
            }
            else
            {
                direction = false;
            }

            return direction;
        }
        while (temp->next != NULL)
        {
            if (temp->data > pos)
            {
                temp = temp->next;
            }
            else
            {
                flag = true;
                break;
            }
        }
        if (flag == false)
        {
            return true;
        }
        temp = head;
        while (temp->next != NULL)
        {
            if (temp->data < pos)
            {
                temp = temp->next;
            }
            else
            {
                flag = true;
                break;
            }
        }
        if (flag == false)
        {
            return false;
        }
        temp = head;
        int up = 0;
        int down = 0;
        while (temp->next != NULL)
        {
            if (temp->data > pos)
            {
                up++;
                temp = temp->next;
            }
            else
            {
                down++;
                temp = temp->next;
            }
        }
        if (up > down)
        {

            return true;
        }
        else if (down > up)
        {

            return false;
        }
        else
        {
            return direction;
        }
    }
    else
    {
        return direction;
    }
}

//we introduced the concept of fetch_till to find the floor till which the lift will continue to go
//so that it will not change the direction otherwise.
int fetch_till(struct floor *head, bool direction)
{
    int ret;
    struct floor *temp = head;
    if (temp != NULL)
    {
        ret = temp->data;
        if (direction == true)
        {
            while (temp->next != NULL)
            {
                if (temp->data > ret)
                {
                    ret = temp->data;
                }
                temp = temp->next;
            }
            if (temp->data > ret)
            {
                ret = temp->data;
            }
            return ret;
        }
        else
        {
            while (temp->next != NULL)
            {
                if (temp->data < ret)
                {
                    ret = temp->data;
                }
                temp = temp->next;
            }
            if (temp->data < ret)
            {
                ret = temp->data;
            }
            return ret;
        }
    }
    else
    {
        return -1;
    }
}

int main()
{
    printf("----------------------Elevetor Management System------------------------\n");
    int h, pos;
    printf("Enter the height of the building and position of the lift ");
    scanf("%d %d", &h, &pos);
    struct floor *head = NULL;
    int till = -1;
    bool direction = true;
    int people_count;
    int no_people;

    // true - up
    // false - down
    while (1)
    {
        head = remove_people(head, pos);
        printf("\n");
        print_link_list(head);

        printf("-------------- FLOOR %d -------------\n", pos);
        people_count = count_people(head);
        printf("People in lift : %d\n", people_count);
        //check condition for overweight - max capacity in elevator is 10
        //if the lift is already full than it will not stop on any other floors and will display-Skipping this floor
        //it will stop at the next nearest floor along its direction.
        if (people_count == 10)
        {
            printf("Lift is full. Skipping the floor.\n");
        }
        else
        {
            do{
                printf("Enter the number of people who want to enter the lift: \n");
                scanf("%d", &no_people);
                if (no_people +  people_count<= 10)
                {
                    break;
                }
                else
                {
                    printf("The lift is full. Please enter a valid number of people\n");
                }
            }while(1);
            if (no_people == -1)
            {
                break;
            }
            else if (no_people > -1 && no_people <= h)
            {
                if (no_people == 0)
                {
                    printf("No one wants to enter the lift.\n");
                }
                else
                {
                    head = add(head, no_people, pos);
                }
            }
            else
            {
                printf("Invalid input\n");
            }
        }
        if (till == -1 || till == pos)
        {
            direction = fetch_direction(head, direction, pos);
            till = fetch_till(head, direction);
        }
        else
        {
            printf(" << CHECK SKIPPED TILL FLOOR %d >> ", till);
        }
        if (direction == true)
        {
            if (pos == h)
            {
                direction = false;
                pos--;
            }
            else
            {
                pos++;
            }
        }
        else
        {
            if (pos == 0)
            {
                direction = true;
                pos++;
            }
            else
            {
                pos--;
            }
        }
        printf("\n");
        print_link_list(head);
    }
}
