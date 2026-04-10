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
        public string Font { get; set; }
    }
}
