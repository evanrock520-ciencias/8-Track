#pragma once
#include "domain/repositories/ITransactionManager.hpp"

namespace Track8::Database {

/**
 * @class TransactionScope
 * @brief Administrador RAII para transacciones sobre un ITransactionManager.
 */
class TransactionScope {
public:
    explicit TransactionScope(Repositories::ITransactionManager& manager)
        : m_manager(&manager) {
        m_active = m_manager->transaction();
    }

    ~TransactionScope() {
        if (m_active && m_manager) {
            m_manager->rollback();
        }
    }

    bool commit() {
        if (m_active && m_manager && m_manager->commit()) {
            m_active = false;
            return true;
        }
        return false;
    }

    TransactionScope(const TransactionScope&) = delete;
    TransactionScope& operator=(const TransactionScope&) = delete;

    TransactionScope(TransactionScope&& other) noexcept
        : m_manager(other.m_manager), m_active(other.m_active) {
        other.m_manager = nullptr;
        other.m_active = false;
    }

    TransactionScope& operator=(TransactionScope&& other) noexcept {
        if (this != &other) {
            if (m_active && m_manager) {
                m_manager->rollback();
            }
            m_manager = other.m_manager;
            m_active = other.m_active;
            other.m_manager = nullptr;
            other.m_active = false;
        }
        return *this;
    }

private:
    Repositories::ITransactionManager* m_manager = nullptr;
    bool m_active = false;
};

} // namespace Track8::Database
