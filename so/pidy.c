int main()
{
   printf("\nPID %d\n", getpid());
   printf("\nUID %d\n", getuid());
   printf("\nPGID %d\n", getpgid());
   printf("\nGID %d\n", getgid());
   getpid();
   sleep(1000);
   return 0;
}
