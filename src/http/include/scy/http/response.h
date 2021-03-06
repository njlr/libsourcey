///
//
// LibSourcey
// Copyright (c) 2005, Sourcey <http://sourcey.com>
//
// SPDX-License-Identifier: LGPL-2.1+
//
/// @addtogroup http
/// @{


#ifndef SCY_HTTP_Response_H
#define SCY_HTTP_Response_H


#include "scy/datetime.h"
#include "scy/http/cookie.h"
#include "scy/http/message.h"

#include <sstream>


namespace scy {
namespace http {


/// HTTP Response Status Codes
enum class StatusCode
{
    Continue = 100,
    SwitchingProtocols = 101,

    OK = 200,
    Created = 201,
    Accepted = 202,
    NonAuthoritative = 203,
    NoContent = 204,
    ResetContent = 205,
    PartialContent = 206,

    MultipleChoices = 300,
    MovedPermanently = 301,
    Found = 302,
    SeeOther = 303,
    NotModified = 304,
    UseProxy = 305,
    // SwitchProxy = 306, not used
    TemporaryRedirect = 307,

    BadRequest = 400,
    Unauthorized = 401,
    PaymentRequired = 402,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    NotAcceptable = 406,
    ProxyAuthRequired = 407,
    RequestTimeout = 408,
    Conflict = 409,
    Gone = 410,
    LengthRequired = 411,
    PreconditionFailed = 412,
    EntityTooLarge = 413,
    UriTooLong = 414,
    UnsupportedMediaType = 415,
    RangeNotSatisfiable = 416,
    ExpectationFailed = 417,
    UnprocessableEntity = 422,
    UpgradeRequired = 426,

    InternalServerError = 500,
    NotImplemented = 501,
    BadGateway = 502,
    Unavailable = 503,
    GatewayTimeout = 504,
    VersionNotSupported = 505
};


/// This class encapsulates an HTTP response message.
class HTTP_API Response : public http::Message
{
public:
    /// typedef std::shared_ptr<Response> Ptr;

    /// Creates the Response with OK status.
    Response();

    /// Creates the Response with the given status  and reason phrase.
    Response(StatusCode status, const std::string& reason);

    /// Creates the Response with the given version, status and reason phrase.
    Response(const std::string& version, StatusCode status,
             const std::string& reason);

    /// Creates the Response with the given status
    /// an an appropriate reason phrase.
    Response(StatusCode status);

    /// Creates the Response with the given version, status
    /// an an appropriate reason phrase.
    Response(const std::string& version, StatusCode status);

    /// Destroys the Response.
    virtual ~Response();

    /// Sets the HTTP status code.
    ///
    /// The reason phrase is set according to the status code.
    void setStatus(StatusCode status);

    /// Returns the HTTP status code.
    StatusCode getStatus() const;

    /// Sets the HTTP reason phrase.
    void setReason(const std::string& reason);

    /// Returns the HTTP reason phrase.
    const std::string& getReason() const;

    /// Sets the HTTP status code and reason phrase.
    void setStatusAndReason(StatusCode status, const std::string& reason);

    /// Sets the Date header to the given date/time value.
    void setDate(const Timestamp& dateTime);

    /// Returns the value of the Date header.
    Timestamp getDate() const;

    /// Adds the cookie to the response by
    /// adding a Set-Cookie header.
    void addCookie(const Cookie& cookie);

    /// Returns a vector with all the cookies set in the response header.
    ///
    /// May throw an exception in case of a malformed Set-Cookie header.
    void getCookies(std::vector<Cookie>& cookies) const;

    /// Writes the HTTP response headers to the given output stream.
    void write(std::ostream& ostr) const;

    /// Writes the HTTP response headers to the given output string.
    void write(std::string& str) const;

    /// Returns true if the HTTP response code was successful (>= 400).
    virtual bool success() const;

    friend std::ostream& operator<<(std::ostream& stream, const Response& res)
    {
        res.write(stream);
        return stream;
    }

private:
    Response(const Response&);
    Response& operator=(const Response&);

    StatusCode _status;
    std::string _reason;
};


const char* getStatusCodeReason(StatusCode status);


} // namespace http
} // namespace scy


#endif


/// @\}
