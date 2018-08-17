//
//
//
#include <string>
#include <list>
#include <thread>
#include <atomic>
#include <functional>

namespace HTTPRequest
{
    using response_callback_type = std::function<void(const std::string &aResponse)>;
    
    using header_list_type = std::list<const std::string>;

    enum class Status
    {
        Pending,
        Succeeded,
        Failed,
    };

    /*!
     \brief common API and implementation for all Request types
    */
    struct Abstract
    {
        /// Check if the request has completed or not
        Status getStatus() const;

        /// brief call either m_OnSuccess or m_OnFailure depending on status
        void performResponseCallback() const;

        Abstract(const response_callback_type &aOnSuccess, const response_callback_type &aOnFailure, std::thread &&aWorker);

    protected:
        response_callback_type m_OnSuccess;
        response_callback_type m_OnFailure;

        std::thread m_Worker;

        std::atomic<Status> m_Status = {Status::Pending};
        
        std::string m_Response = {};

    public:
        virtual ~Abstract() = 0;

        //Abstract(const Abstract &a) = default;
        //Abstract(Abstract &&a) = default;
    };

    /*!
     \brief POST method requests that the server accept the entity enclosed in the request as a new subordinate of the web resource identified by the URI
    */
    struct Post final : public Abstract
    {
        Post(const std::string &aURL, const header_list_type &aHeaders, const std::string &aBody, const response_callback_type &aOnSuccessCallback, const response_callback_type &aOnFailedCallback);
    };

    /*!
     \brief GET method requests a representation of the specified resource. Requests using GET should only retrieve data and should have no other effect.
    */
    struct Get final : public Abstract
    {
        Get(const std::string &aURL, const header_list_type &aHeaders, const response_callback_type &aOnSuccessCallback, const response_callback_type &aOnFailedCallback);
    };
}
