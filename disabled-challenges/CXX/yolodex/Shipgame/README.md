# Sample Shipgame

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

This is a simple HTTP-proxy like service. This is an IPC cb where the main CB acts as a router and all other CBs act as individual web-servers. The protocol is very simple with three possible commands:

HELLO I AM [name] : Used by the client to initiate a conenction with the router
HELLO [name] YOUR UID IS [uid] HOW CAN I HELP YOU : Used by the router to acknowledge the client
[uid] SAYS GET [url] PLEASE : Used by the client to retrieve a specific page.
GOODBYE : Used by the client to close the link. GOODBYE is also echoed by the router.
BAD CMD : Used by the router to report a parsing error to the client.
SERVER NOT FOUND : Used by the router to report an invalid server

## Vulnerability Class: 

Classic format string vulnerability that falls under [CWE-134: Uncontrolled Format String](http://cwe.mitre.org/data/definitions/134.html).

## Additional Notes:

A python script - textIntoPageData.py is provided to generate the pages.data file that is included into the CBs. This acts as their internal page database
