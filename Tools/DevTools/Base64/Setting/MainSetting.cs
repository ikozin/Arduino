using System.Text.Json.Serialization;

namespace Base64Encoder.Setting
{
    public class MainSetting
    {
        public MainSetting()
        {
            Font = "Roboto; 10,2";
        }

        [JsonRequired]
        [JsonPropertyName("font")]
        public required string Font { get; set; }
    }
}
