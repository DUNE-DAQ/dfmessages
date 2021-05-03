// Schema for request types in dfmessages
//

local moo = import "moo.jsonnet";
local s = moo.oschema.schema("dunedaq.dfmessages.requesttypes");

// A temporary schema construction context.
local cs = {
    requesttype: s.enum("RequestType",
                        ["kDFReadout", "kDQMReadout", "kSNBRequest", "kInvalidMode"],
                        "kInvalidMode",
                        doc="The different request types")

};
// Output a topologically sorted array.
moo.oschema.sort_select(cs)