#include <iostream>
#include <pthread.h>

#define THREAD_STACK 1048576
typedef long long ll;

static void* NumbSum(void* numb)
{
    ll n = *((ll *)numb);
    ll sum = n * ( 2 + (n - 1) ) / 2;
    return (void *)sum;
}

int main(int argc, char** argv)
{   
    if (argc < 2)
    {
        std::cerr << "Need to pass one parameter!\nUsage : " << argv[0] << std::endl;
        return -1;
    }

    ll numb = atoll(argv[1]);

    pthread_attr_t attr;
    pthread_t thread;

    pthread_attr_init(&attr);

    std::size_t thread_stack_size = THREAD_STACK;
    void* stack_addr_base = (void *)malloc(thread_stack_size);

    if ( 0 != pthread_attr_setstack(&attr, stack_addr_base, thread_stack_size) )
    {
        std::cerr << "Setting stack error!" << std::endl;
        free(stack_addr_base);
        return -1;
    }

    ll result = 0;

    pthread_create( &thread, &attr, NumbSum, (void *)&numb);
    pthread_join(thread, (void **)&result);

    free(stack_addr_base);

    std::cout << result << std::endl;

    return 0;
}
