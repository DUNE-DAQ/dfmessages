// Schema for request types in dfmessages
//

local moo = import "moo.jsonnet";
local s = moo.oschema.schema("dunedaq.dfmessages.request_modes");

// A temporary schema construction context.
local cs = {
    request_mode: s.enum("mode_t",
                        ["kDFReadout", "kDQMReadout", "kSNBRequest", "kInvalidMode"],
                        "kInvalidMode",
                        doc="The different request types")

};
// Output a topologically sorted array.
moo.oschema.sort_select(cs)