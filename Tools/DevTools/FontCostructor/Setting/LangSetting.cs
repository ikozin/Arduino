using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace FontCostructor.Setting
{
    public class LangSetting
    {
        [JsonRequired]
        [JsonPropertyName("lang")]
        public required string Lang { get; set; }

        [JsonRequired]
        [JsonPropertyName("value")]
        public required string Value { get; set; }

        public override string ToString()
        {
            return Lang.ToString();
        }
    }
}
