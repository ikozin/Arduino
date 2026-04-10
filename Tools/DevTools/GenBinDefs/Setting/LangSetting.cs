using System.Text.Json.Serialization;

namespace GenBinDefs.Setting
{
    public class LangSetting
    {
        [JsonRequired]
        [JsonPropertyName("lang")]
        public string Lang { get; set; } = String.Empty;

        [JsonRequired]
        [JsonPropertyName("header")]
        public string Header { get; set; } = String.Empty;

        [JsonRequired]
        [JsonPropertyName("prefix")]
        public string Prefix { get; set; } = String.Empty;

        [JsonRequired]
        [JsonPropertyName("value")]
        public string Value { get; set; } = String.Empty;

        [JsonRequired]
        [JsonPropertyName("defines")]
        public string[] Defines { get; set; } = new string[0];

        [JsonRequired]
        [JsonPropertyName("footer")]
        public string Footer { get; set; } = String.Empty;
    }
}
