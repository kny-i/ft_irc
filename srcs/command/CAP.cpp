#include <Command.hpp>

/**
 * @brief allows IRC clients and servers to negotiate new features in a backwards-compatible way
 *
 * CAP LS | CAP END
 */
void CAP(Client &client, std::vector<struct pollfd> &pollfds, std::map<int, Client> &users, std::map<std::string, int> &nick_to_fd) {
	const int &fd = client.getFd();

	if (client.getParams().at(0) == "LS")
		sendMessage(fd, CAP_LS, 0);
	else if (client.getParams()[0] == "END") {
		if (client.should_be_cap_nick == false || client.should_be_cap_pass == false) {
			clearClientInfo(client, pollfds, users, nick_to_fd);
			return;
		}
		sendWelcomeMessage(client);
	}
}
