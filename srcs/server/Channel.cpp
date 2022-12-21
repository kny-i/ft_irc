#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel() {}

Channel::~Channel(){}


const std::vector<Client> &Channel::getMember() const { return members_; }
const std::string &Channel::getTopic() const { return topic_; }
const std::string &Channel::getName() const { return name_; }
const std::string &Channel::getKey() const { return key_; }
const std::vector<std::string> &Channel::getOper() const { return opers_; }
void Channel::setMember(Client &member) { members_.push_back(member); }
void Channel::setName(std::string name) { name_ = name; }
void Channel::setKey(std::string key) { key_ = key; }
void Channel::setTopic(std::string topic) { topic_ = topic; }
void Channel::addOper(std::string name) { opers_.push_back(name); }

bool Channel::is_inChannel(std::string const &nick_nme)  {

	std::vector<Client> const &members = this->getMember();
	for (std::vector<Client>::const_iterator  it = members.begin(); it !=members.end(); it++) {
		if (it->getNickname() == nick_nme) {
			return true;
		}
	}
	return false;
}

bool Channel::is_operator(const std::string &nick_name) {

	std::vector<std::string> const  &members = this->getOper();
	for (std::vector<Client>::const_iterator  it = members.begin(); it != members.end(); it++) {
		if (it->getNickname() == nick_nme) {
			return true;
		}
	}
	return false;
}