#include "passwd.h"


static int is_registered(char *uname) {
	// Open your passwd storage file
	// Find if the User is present
	// return 1 if found
	// else return 0
	return 0;
}

int register_user(char *uname, char *passwd) {
	// Check if password store file is present
	// Create it if not present
	// Look for sane permission on file
	
	if (is_registered(uname)) {
		fprintf(stderr, "Choose another username\n");
		return 0;
	}
	// Open the password file and append the username and password
	// Dont append the password in plain text. Try something obscure.
	// If you are out of ideas look for how unix implements passwords.



	return 1;
}

int auth_user(char *uname, char *passwd) {
	// check if password store is present
	// if not return 0
	
	if (is_registered(uname)) {
		fprintf(stderr, "User not registered\n");
		return 0;
	}

	// Parse the file and then compare username and password supplied.
	// If you recall password is not plain text...
	
	//return 0/1 depending on if the password was correct or not
}

/* Feel Free to add to functions to the already pathetic design.
 * You try creating these assignments sometime ... */

