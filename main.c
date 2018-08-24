#include <stdio.h>

typedef struct user {
	int uid;
	char *name;
} user;

typedef struct fileACL {
	char *name;
	int uid[100];
	int read[100];
	int write[100];
	int execute[100];
} fileACL;

user newUser(int id, char *n);
fileACL newFile(char *n, int x);
void setPermissions(user *u, fileACL *f, int r, int w, int x);
void readFile(user *u, fileACL *f);
void writeFile(user *u, fileACL *f);
void executeFile(user *u, fileACL *f);

int main(){
	user users[3];
	users[0] = newUser(1010, "UserA");
	users[1] = newUser(1011, "UserB");
	users[2] = newUser(1012, "UserC");
	int n = sizeof(users)/sizeof(users[0]);

	fileACL files[2];
	files[0] = newFile("File1", n);
	files[1] = newFile("File2", n);
	int m = sizeof(files)/sizeof(files[0]);

	int i;
	for(i = 0; i < n; i++){
		switch(users[i].uid){
			case 1010 : {
				setPermissions(&users[i], &files[0], 1, 1, 1);
				setPermissions(&users[i], &files[1], 0, 0, 0);
				break;
			};
			case 1011 : {
				setPermissions(&users[i], &files[0], 1, 0, 1);
				setPermissions(&users[i], &files[1], 1, 1, 0);
				break;
			};
			case 1012 : {
				setPermissions(&users[i], &files[0], 0, 0, 1);
				setPermissions(&users[i], &files[1], 1, 1, 1);
				break;
			};
		}	
	}

	printf("\nPermission Tests:\n");
	executeFile(&users[0], &files[1]);
	readFile(&users[1], &files[0]);
	readFile(&users[1], &files[1]);
	writeFile(&users[2], &files[0]);

	return 0;
}

user newUser(int id, char *n){
	user u;
	u.uid = id;
	u.name = n;
	return u;
}

fileACL newFile(char *n, int x){
	int a[x];
	fileACL f;
	f.name = n;
	return f;
}

void setPermissions(user *u, fileACL *f, int r, int w, int x){
	int i;
	int n = sizeof(f[0].uid)/sizeof(f[0].uid[0]);
	for(i = 0; i < n; i++){
		if(f->uid[i] == 0){
			f->uid[i] = u->uid;
			f->read[i] = r;
			f->write[i] = w;
			f->execute[i] = x;
			printf("User: %s | File: %s | Read: %d, Write: %d, Execute: %d\n", 
				u->name, f->name, f->read[i], f->write[i], f->execute[i]);
			break;
		}
	}
}

void readFile(user *u, fileACL *f){
	char *access = "denied";
	int i;
	int n = sizeof(f[0].uid)/sizeof(f[0].uid[0]);
	for(i = 0; i < n; i++){
		if(f->uid[i] == u->uid){
			if(f->read[i]){
				access = "granted";
			}
		} 
	}
	printf("%s read access to %s is %s\n", u->name, f->name, access);
}

void writeFile(user *u, fileACL *f){
	char *access = "denied";
	int i;
	int n = sizeof(f[0].uid)/sizeof(f[0].uid[0]);
	for(i = 0; i < n; i++){
		if(f->uid[i] == u->uid){
			if(f->write[i]){
				access = "granted";
			}
		} 
	}
	printf("%s write access to %s is %s\n", u->name, f->name, access);
}

void executeFile(user *u, fileACL *f){
	char *access = "denied";
	int i;
	int n = sizeof(f[0].uid)/sizeof(f[0].uid[0]);
	for(i = 0; i < n; i++){
		if(f->uid[i] == u->uid){
			if(f->execute[i]){
				access = "granted";
			}
		} 
	}
	printf("%s execute access to %s is %s\n", u->name, f->name, access);
}
