#include "widen/common/proto_wrapper/proto_wrapper.hpp"
#include "widen/common/proto_wrapper/identifier.hpp"

namespace widen
{
    class JoinRequest final : public ProtoWrapper
    {
    public:
        JoinRequest(const std::string &ip, const int64_t timestamp);
        JoinRequest(const Identifier &identifier);

        std::string toString() const override;

        void deserialize(const std::string &byteString) override;

    protected:
        std::string rawSerialize() const override;

    private:
        proto::JoinRequestProto proto;
        Identifier identifer;
    };
}