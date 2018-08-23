// © 2018 Joseph Cameron - All Rights Reserved

#include "gdk/httprequest.h"

#include <gdkresources/buildinfo.h>

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Linux || defined JFC_TARGET_PLATFORM_Windows
    #include <curl/curl.h>
#endif

using namespace HTTPRequest;

static constexpr auto TAG = "HTTPRequest";

// ============================================================

static void try_initialize_curl()
{
    static bool initialized = false;

    if (auto curlErrorNumber = curl_global_init(CURL_GLOBAL_ALL)) 
        throw std::runtime_error(std::string(TAG) + ": " "Curl global init failed with error: " + std::to_string(curlErrorNumber));

    initialized = true;
}

static void uninitialize_curl()
{
    curl_global_cleanup(); //Put at module termination?
}

// ============================================================

Abstract::Abstract(const response_callback_type &aOnSuccess, const response_callback_type &aOnFailure, std::thread &&aWorker)
: m_Worker(std::move(aWorker))
, m_OnSuccess(aOnSuccess)
, m_OnFailure(aOnFailure)
{}

Abstract::~Abstract()
{
    m_Worker.detach();
}

Status Abstract::getStatus() const
{
    return m_Status;
}

void Abstract::performResponseCallback() const
{
    switch ((Status)m_Status)
    {
        case Status::Succeeded:
        {
            m_OnSuccess(m_Response);
        } break;

        case Status::Failed:
        {
            m_OnFailure(m_Response);
        } break;

        default: break;
    }
}

// ============================================================

Post::Post(const std::string &aURL, const header_list_type &aHeaders, const std::string &aBody, const response_callback_type &aOnSuccessCallback, const response_callback_type &aOnFailedCallback)
: Abstract(aOnSuccessCallback, aOnFailedCallback, std::thread([&](const header_list_type &aHeaders, const std::string &aBody)
{
    try_initialize_curl();

    if (CURL *const curl = curl_easy_init()) 
    {
        // Populate request        
        curl_easy_setopt(curl, CURLOPT_URL, aURL.c_str());

        struct curl_slist *headersLinkedList = nullptr;
        for (const auto &header : aHeaders) headersLinkedList = curl_slist_append(headersLinkedList, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headersLinkedList);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, aBody.c_str());

        // Setup response handlers
        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(const char *const, const size_t, const size_t, void *const)>
        (
            [](const char *const contents, const size_t size, const size_t nmemb, void *const userp)
            {
                ((std::string *const)userp)->append((const char *const)contents, size * nmemb);

                return size * nmemb;
            }
        ));

        // Collect response
        if (const auto errorCode = curl_easy_perform(curl))
        {
            m_Response = curl_easy_strerror(errorCode);

            m_Status = Status::Failed;
        }
        else
        {
            m_Response = readBuffer;

            m_Status = Status::Succeeded;
        }

        curl_easy_cleanup(curl);

        curl_slist_free_all(headersLinkedList);
    }
    else throw std::runtime_error(std::string(TAG) + ": " "Could not create a curl handle with curl_easy_init");
}
, aHeaders
, aBody
)){}

// ==============================================================================================================================

Get::Get(const std::string &aURL, const header_list_type &aHeaders, const response_callback_type &aOnSuccessCallback, const response_callback_type &aOnFailedCallback)
: Abstract(aOnSuccessCallback, aOnFailedCallback, std::thread([&](const header_list_type &aHeaders)
{
    try_initialize_curl();

    if (CURL *const curl = curl_easy_init()) 
    {
        // Populate request        
        curl_easy_setopt(curl, CURLOPT_URL, aURL.c_str());

        struct curl_slist *headersLinkedList = nullptr;
        for (const auto &header : aHeaders) headersLinkedList = curl_slist_append(headersLinkedList, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headersLinkedList);

        // Setup response handlers
        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(const char *const, const size_t, const size_t, void *const)>
        (
            [](const char *const contents, const size_t size, const size_t nmemb, void *const userp)
            {
                ((std::string *const)userp)->append((const char *const)contents, size * nmemb);

                return size * nmemb;
            }
        ));

        // Collect response
        if (const auto errorCode = curl_easy_perform(curl))
        {
            m_Response = curl_easy_strerror(errorCode);

            m_Status = Status::Failed;
        }
        else
        {
            m_Response = readBuffer;

            m_Status = Status::Succeeded;
        }

        curl_easy_cleanup(curl);

        curl_slist_free_all(headersLinkedList);
    }
    else throw std::runtime_error(std::string(TAG) + ": " "Could not create a curl handle with curl_easy_init");
}
, aHeaders
)){}

// ==============================================================================================================================
