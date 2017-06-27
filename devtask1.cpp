#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { EXIT, SYS, EXEC, FORK, DAEMON };

void MENU();
int SYS_CREATION_PROC();
void EXEC_CREATION_PROC();
void FORK_CREATION_PROC();
void DEAMONFORK_CREATION_PROC();

int main(int argc, char** argv)
{
    MENU();
    return 0;
}

void MENU()
{
    bool CHECK_INPUT = true;
    while (CHECK_INPUT)
    {
        std::cout << "The main program process ID is "<< (int)getpid() << std::endl << std::endl;
        int choice;

        std::cout << "****************************************************\n"
                     "****\t1.\tSYSTEM creation process\t\t****\n"
                     "****\t2.\tEXEC creation process\t\t****\n"
                     "****\t3.\tFORK creation process\t\t****\n"
                     "****\t4.\tDAEMON creation process\t\t****\n"
                     "****\t0.\t\tEXIT\t\t\t****\n"
                     "****************************************************\n";
        std::cout << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case SYS:
            system("clear");
            if(SYS_CREATION_PROC() != 127 || SYS_CREATION_PROC() != -1)
                std::cout << "SYSTEM creation process successful" << std::endl << std::endl;
            else
                std::cerr << "SYSTEM creation process f a i l e d" << std::endl << std::endl;
            break;
        case EXEC:
            system("clear");
            EXEC_CREATION_PROC();
            break;
        case FORK:
            system("clear");
            FORK_CREATION_PROC();
            break;
        case DAEMON:
            system("clear");
            DEAMONFORK_CREATION_PROC();
            break;
        case EXIT:
            system("clear");
            CHECK_INPUT = false;
            break;
        default:
            system("clear");
            std::cout << "Incorrect i n p u t !" << std::endl << std::endl;
        }
    }
}

int SYS_CREATION_PROC()
{
    int return_value;
    return_value = system ( "ls -l /" );
    return return_value;
}

void EXEC_CREATION_PROC()
{
    pid_t _pid = fork();
    std::cout << "PID --- " << _pid << std::endl;
    if (_pid == 0)
        execl("/bin/ls", "ls", "-r", "-t", "-l", (char *) NULL);
    wait(&_pid);
    std::cout << "DONE" << std::endl << std::endl;
    std::cout << "EXEC creation process successful" << std::endl << std::endl;
}

void FORK_CREATION_PROC()
{
    pid_t _pid;
    int status;
    if((_pid = fork()) < 0 )
    {
        std::cerr << "FORK f a i l e d !" << std::endl;;
        return;
    }
    std::cout << "The FORK process ID is " << (int)_pid << std::endl;
    if((_pid = waitpid(_pid, &status, 0)) && WIFEXITED(status))
    {
        std::cout << "The FORK process ( ID = " << _pid << " ) finished execution\n";
        std::cout << "Exit code " << WEXITSTATUS(status) << std::endl << std::endl;
    }
}

void DEAMONFORK_CREATION_PROC()
{
    pid_t _pid;

    if((_pid = fork()) < 0 )
    {
        std::cerr << "FORK f a i l e d !" << std::endl;
        exit(1);
    }
    else if (_pid != 0 )
    {
        exit(0);
    }

    std::cout << "DEAMON starting ... " << std::endl;
    std::cout << "( To finish d a e m o n execution, exec gnome-terminal and kill him by PID )\n"
                 "( \t\tIt will be the last PID of main program\t\t\t   )"<< std::endl << std::endl;
    setsid();
    //signal (SIGHUP, SIG_IGN);
    daemon(1, 1);
}
