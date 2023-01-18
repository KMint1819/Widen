# Protocol

- Requests
    - 4 byte unsigned int that represents length of header
    - Header that contains information of the body. See [the protobuf definition](../protos/widen/general.proto)
    - The body. Length is specified in the header
- Responses
    > Because response is directly sent through the same socket from where the requests
    came from, a header that specifies its type is unnecessary.
    - 4 byte unsigned int that represents length of body 
    - The body. 