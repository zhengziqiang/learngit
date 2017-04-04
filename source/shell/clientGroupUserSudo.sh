#!/bin/bash

if [ $# != 2 ]; then
    echo -ne "Arguments Error.\n"
    echo -ne "Usage:\n"
    echo -ne "\t$0 GroupName UserList\n"
    exit 77
fi

GroupName=$1
UserList=$2
SUDOERS="/etc/sudoers"
SUDOERSDIR="/etc/sudoers.d"
INCLUDEDIR="#includedir /etc/sudoers.d"

#echo "===== Checking sudo ====="
#if [ -f /etc/sudoers ]
#then
#	echo "sudo is already installed."
#else
#	echo "Installing sudo ..."
#	apt-get update
#	apt-get install sudo
#fi

#echo "===== Checking sudo '#include' ====="
#cat ${SUDOERS} | grep "${INCLUDEDIR}" >/dev/null 2>&1
#if [ $? -eq 0 ]
#then
#	echo "sudo has '${INCLUDEDIR}' configurated."
#else
#	echo "Configurating '${SUDOERS}' by adding '${INCLUDEDIR}' ..."
#	chmod +w ${SUDOERS}
#	echo "" >> ${SUDOERS}
#	echo ${INCLUDEDIR} >> ${SUDOERS}
#	chmod -w ${SUDOERS}
#fi

echo "===== Checking group ====="
awk -F: '{print $1}' /etc/group | grep -w ${GroupName} >/dev/null 2>&1
if [ $? -eq 0 ]
then
	echo "Group '${GroupName}' is already exist."
else
	echo "Adding group '${GroupName}' ..."
	groupadd ${GroupName}
fi
if [ ! -d /home/${GroupName} ]; then
    mkdir -p /home/${GroupName}
fi

echo "===== Checking users ====="
cat ${UserList} | while read user
do
	awk -F: '{print $1}' /etc/passwd | grep -w $user >/dev/null 2>&1
	if [ $? -eq 0 ]
	then
		echo "User '$user' is already exist."
	else
		echo "Adding '$user' ..."
		useradd -d /home/${GroupName}/$user -m -g ${GroupName} -s /bin/bash $user
		echo $user:$user | chpasswd
	fi
	echo "Adding file ${SUDOERSDIR}/$user ..."
	echo "$user	ALL=(ALL:ALL) ALL" > ${SUDOERSDIR}/$user
done

echo "member	ALL=(ALL:ALL) ALL" > ${SUDOERSDIR}/member

echo "===== WELL DONE! ====="
