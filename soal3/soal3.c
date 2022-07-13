#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> //pid_t
#include <unistd.h> //fork()
#include <syslog.h>
#include <wait.h>
#include <dirent.h>
#include <sys/unistd.h>
#include <sys/wait.h>

int main() {
	pid_t child_darat;
	pid_t child_air;
	pid_t child_unzip_animal;
	pid_t child_folder_darat;
	pid_t child_folder_darat_coba;
	pid_t child_folder_air;
	pid_t child_folder_air_coba;
	pid_t child_folder_hapus;
	pid_t child_folder_hapus_bird;
	pid_t child_folder_hapus_darat_bird;
	pid_t child_folder_bikin_file;
	pid_t child_folder_pindah_file;
	int status;

	child_darat = fork();
  
	if (child_darat < 0) 
	{
		exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
	}

	if (child_darat == 0) 
	{
	// this is child
		char *argv[] = {"mkdir", "-p", "darat", NULL};
		execv("/bin/mkdir", argv);
	} 	
		else {
		// this is parent
	 		while ((wait(&status)) > 0);
	  		child_air = fork();
  
	if (child_air < 0) {
    		exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
 	}

 	if (child_air == 0) {
    	// this is child
    		sleep (3);
		char *argv[] = {"mkdir", "-p", "air", NULL};
		execv("/bin/mkdir", argv);
 	 } 
	else
		{
					child_unzip_animal = fork();
			
						if (child_unzip_animal < 0)
							{
								exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
							}
						if (child_unzip_animal == 0) 
							{
								// this is child
								char *argv[] = {"unzip", "animal.zip", NULL}; //
								execv("/usr/bin/unzip", argv);
							}
		else
		{ 
			while((wait(&status)) > 0);
			child_folder_darat = fork();

			if(child_folder_darat < 0)
				{
					exit(EXIT_FAILURE);
				}

			if(child_folder_darat == 0)
				{
					execl("/usr/bin/find", "find", "/home/depede/modul2/animal", "-type", "f", "-name", "*darat.jpg", "-exec", "mv", "-t", "/home/depede/modul2/darat", "{}", "+", (char *) NULL);
				}

				else
					{
						while((wait(&status)) > 0);
						child_folder_air = fork();

						if(child_folder_air < 0)
						{
							exit(EXIT_FAILURE);
						}

						if(child_folder_air == 0)
						{
							//execl("/usr/bin/find", "find", "/home/kali/modul2/animal/", "-mindepth", "1", "-type", "d", "-name", "*", "-exec", "mv", "-t", "/home/kali/modul2/animal/darat/", "{}", "+", (char *) NULL);
							execl("/usr/bin/find", "find", "/home/depede/modul2/animal", "-type", "f", "-name", "*air.jpg", "-exec", "mv", "-t", "/home/depede/modul2/air", "{}", "+", (char *) NULL);

						}
					}
		} 


			while((wait(&status)) > 0);
			child_folder_darat_coba = fork();

       		if(child_folder_darat_coba < 0)
				{
					exit(EXIT_FAILURE);
				}

       		 if(child_folder_darat_coba == 0)
				{
					execl("/usr/bin/find", "find", "/home/depede/modul2/animal", "-type", "f", "-name", "*bird.jpg", "-exec", "mv", "-t", "/home/depede/modul2/darat", "{}", "+", (char *) NULL); 
				}

			else
			{
				while((wait(&status)) > 0);
				child_folder_air_coba = fork();

				if(child_folder_air_coba < 0)
				{
					exit(EXIT_FAILURE);
				}

				if(child_folder_air_coba == 0)
				{
					//execl("/usr/bin/find", "find", "/home/kali/modul2/animal/", "-mindepth", "1", "-type", "d", "-name", "*", "-exec", "mv", "-t", "/home/kali/modul2/animal/darat/", "{}", "+", (char *) NULL);
					execl("/usr/bin/find", "find", "/home/depede/modul2/animal", "-type", "f", "-name", "*fish.jpg", "-exec", "mv", "-t", "/home/depede/modul2/air", "{}", "+", (char *) NULL);
				}

			}


			while((wait(&status)) > 0);
			child_folder_hapus = fork();

       		if(child_folder_hapus < 0)
				{
					exit(EXIT_FAILURE);
				}

       		 if(child_folder_hapus == 0)
				{
					execl("/usr/bin/find", "find", "/home/depede/modul2/animal", "-type", "f", "-name", "*frog.jpg", "-exec", "rm", "-r", "{}", "+", (char*) NULL); 
				}

			else
			{
				while((wait(&status)) > 0);
				child_folder_hapus_bird = fork();

				if(child_folder_hapus_bird < 0)
				{
					exit(EXIT_FAILURE);
				}

				if(child_folder_hapus_bird == 0)
				{
					//execl("/usr/bin/find", "find", "/home/kali/modul2/animal/", "-mindepth", "1", "-type", "d", "-name", "*", "-exec", "mv", "-t", "/home/kali/modul2/animal/darat/", "{}", "+", (char *) NULL);
					execl("/usr/bin/find", "find", "/home/depede/modul2/darat", "-type", "f", "-name", "*bird.jpg", "-exec", "rm", "-r", "{}", "+", (char*) NULL); 
				}
			}

			}
			
			while((wait(&status)) > 0);
			child_folder_hapus_darat_bird = fork();

       		if(child_folder_hapus_darat_bird < 0)
				{
					exit(EXIT_FAILURE);
				}

       		 if(child_folder_hapus_darat_bird == 0)
				{
					execl("/usr/bin/find", "find", "/home/depede/modul2/darat", "-type", "f", "-name", "*bird_darat.jpg", "-exec", "rm", "-r", "{}", "+", (char*) NULL); 
				}

			else
			{
				while((wait(&status)) > 0);
				child_folder_bikin_file = fork();

				if(child_folder_bikin_file < 0)
				{
					exit(EXIT_FAILURE);
				}

				if(child_folder_bikin_file == 0)
				{
					//execl("/usr/bin/find", "find", "/home/kali/modul2/animal/", "-mindepth", "1", "-type", "d", "-name", "*", "-exec", "mv", "-t", "/home/kali/modul2/animal/darat/", "{}", "+", (char *) NULL);
					execl("/usr/bin/touch", "touch", "/home/depede/modul2/air", "list.txt", NULL);
			
				}
			}
			 while((wait(&status)) > 0);
        child_folder_pindah_file = fork();

        if(child_folder_pindah_file < 0){
          exit(EXIT_FAILURE);
        }

        if(child_folder_pindah_file == 0){
          //execl("/usr/bin/find", "find", "/home/kali/modul2/animal", "-type", "f", "-name", "*air.jpg", "-exec", "mv", "-t", "/home/kali/modul2/air", "{}", "+", (char *) NULL);
           execl("/usr/bin/find", "find", "/home/depede/modul2", "-type", "f", "-name", "*list.txt", "-exec", "mv", "-t", "/home/depede/modul2/air", "{}", "+", (char *) NULL);
     

          
        }
		}
	}	
