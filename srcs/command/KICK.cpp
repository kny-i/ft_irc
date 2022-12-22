#include <Command.hpp>

/*
 * rfc 1459.pdf's 21 page(in 54 page)
 * @params
 * <channel> <user> [<comment>]
 * [important point] only channel operator can kick them out
 * #issue 22
 */

void debug_member_in_channel(Channel const &channel) {
	std::cerr << "<<<members in channel>>>\n";
	for (auto member : channel.getMember()) {
		std::cerr << member.getNickname() << std::endl;
	}
	std::cout << "_____________________________________\n";
}

void debug_channel_in_user(Client &client) {
	std::cerr << "<<<channel joined by the user>>>\n";
	std::cerr << "THE USER : " << client.getNickname() << "\n";
	if (client.getChannels().empty()) {
		std::cerr << "now this use is not belong to any channel!\n";
		return ;
	} else {
		for (auto ch : client.getChannels()) {
			std::cerr << ch.first << std::endl;
		}
	}
	std::cout << "_____________________________________\n";
}

bool is_nick_in_channel(std::string const &nick, Channel &channel) {
	std::vector<Client> const &members = channel.getMember();
	std::vector<Client>::const_iterator it = members.begin();
	for (; it != members.end(); it++) {
		if (nick == it->getNickname()) {
			return true;
		}
	}
	return false;
}
//#ありで送られてくるの見逃してた。。。
void KICK(Client &client, std::map<std::string, Channel> &channels, Server &server) {
	int fd = client.getFd();
	std::string const &nick = client.getNickname();
	std::string param1 = client.getParams()[0];
	param1.erase(param1.begin());
	Channel &channel = channels[param1];
	std::cout << "+++++++++++++++\n"
	<< param1
	<< std::endl
	<< channel.getName()
	<< "__________________________\n";
	std::string const &frightened_person = client.getParams()[1];
	sendMessage(fd, "KICK!!!!!!\r\n", 0);

	if (client.getParams()[0].size() < 2) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "KICK"), 0);
	}
//	else if (channel.getOper() != nick) {
//		sendMessage(fd, ERR_NOPRIVILEGES(nick), 0);
//	} //operatorは複数人いる可能性があるのでvectorになる
//	else if (is_nick_in_channel(frightened_person, channel) == false) {
//		sendMessage(fd, ERR_NOSUCHNICK(frightened_person), 0);
//	} else if (is_nick_in_channel(nick, channel) == false) {
//		sendMessage(fd, ERR_NOTONCHANNEL(nick, channel.getName()), 0);
//		↓未検証
//	} else if (channel.getName().empty()) {
//		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channel.getName()), 0);
//	}
	else {
		std::string reply_mes =
				client.getNickname()
				+ " KICK "
				+ channel.getName()
				+ " "
				+ frightened_person
				+ "\n";
		sendMessage(fd, reply_mes, 0);
		int frightened_person_fd = server.getFd_from_nick(frightened_person);
		std::map<int, Client> sock_client = server.getUsers();
		Client frightened_person_account = sock_client[frightened_person_fd];
		channel.eraseMember(frightened_person_account);

		/* debug member */
//		debug_member_in_channel(channel);
//		debug_channel_in_user(client);
	}
}