using System.Text.Json.Serialization;

namespace GenBinDefs.Setting
{
    public class LangSetting
    {
        [JsonRequired]
        [JsonPropertyName("lang")]
        public required string Lang { get; set; }

        [JsonRequired]
        [JsonPropertyName("header")]
        public required string Header { get; set; }

        [JsonRequired]
        [JsonPropertyName("prefix")]
        public required string Prefix { get; set; }

        [JsonRequired]
        [JsonPropertyName("value")]
        public required string Value { get; set; }

        [JsonRequired]
        [JsonPropertyName("defines")]
        public required string[] Defines { get; set; }

        [JsonRequired]
        [JsonPropertyName("footer")]
        public required string Footer { get; set; }
    }
}
