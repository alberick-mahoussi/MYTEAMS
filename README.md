# B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
 Communication Protocol
    1- Implemented commands
        LOGIN (/login)
            This command sets the user_name used by the client

        LOGOUT (/logout)
            This command disconnects the client from the server

        HELP (/help)
            This command show help

        USERS (/users)
            This command gets the list of all users that exist on the domain

        USER (/user)
            This command gets information about a user

        SEND (/send)
            This command sends a message to a user

        MESSAGES (/messages)
            This command lists all messages exchange with an user

        SUBSCRIBE (/subscribe)
            This command subscribe the client to the event of a team and its sub directories (enable reception
            of all events from a team)

        SUBSCRIBED (/subscribed)
            This command lists all subscribed teams or list all users subscribed to a team

        UNSUBSCRIBE (/unsubscribe)
            This command unsubscribes the client from a team

        USE (/use)
            This command uses specify a context team/channel/thread

        CREATE (/create)
            This command is based on what is being used and creates the sub resource

        LIST (/list)
            This command is based on what is being used and lists all the sub resources

        INFO (/info)
            This command is based on what is being used and lists the current
