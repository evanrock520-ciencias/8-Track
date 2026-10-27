#include "services/ArtistService.hpp"

#include <stdexcept>

namespace Track8::Services {

ArtistService::ArtistService(
    const std::shared_ptr<Repositories::IPerformerRepository>& performers)
    : m_performers(performers) {}

void ArtistService::markAsPerson(const int id) const {
    try {
        m_performers->markAsArtist(id);
    } catch (std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

void ArtistService::markAsPerson(const std::string& name) const {
    const auto performer = m_performers->find(name);
    if (!performer)
        throw std::runtime_error("Performer with name " + name + " not found");
    markAsPerson(performer->id());
}

void ArtistService::markAsGroup(const int id) const {
    try {
        m_performers->markAsGroup(id);
    } catch (std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

void ArtistService::markAsGroup(const std::string& name) const {
    const auto performer = m_performers->find(name);
    if (!performer)
        throw std::runtime_error("Performer with name " + name + " not found");
    markAsGroup(performer->id());
}

void ArtistService::updatePerson(const Domain::Artist& person) const {
    try {
        m_performers->update(person);
    } catch (std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

void ArtistService::updateGroup(const Domain::Group& group) const {
    try {
        m_performers->update(group);
    } catch (std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

void ArtistService::addMember(const int groupId, const int personId) const {
    try {
        m_performers->addToGroup(groupId, personId);
    } catch (std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

void ArtistService::removeMember(const int groupId, const int personId) const {
    try {
        m_performers->removeFromGroup(groupId, personId);
    } catch (std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

} // namespace Track8::Services