using System.Text.Json.Serialization;

namespace IntelHexEncoder.Setting
{
    public class MainSetting
    {
        public MainSetting()
        {
            Font = "Cascadia Mono; 9";
        }

        [JsonRequired]
        [JsonPropertyName("font")]
        public required string Font { get; set; }
    }
}
