<?hh //strict

namespace Money\Currency;

class Loader {
  public static string $DATA_PATH = "/../../resources/";

  public static function load_currencies(): array<string, array<string,mixed>> {
    $currencies = array_merge(
      Loader::parse_currency_file("currency_iso.json"),
      Loader::parse_currency_file("currency_non_iso.json"),
      Loader::parse_currency_file("currency_backwards_compatible.json")
    );

    return $currencies;
  }

  public static function parse_currency_file(string $filename): array<string, array<string,mixed>> {
    $file = file_get_contents(dirname(__FILE__).Loader::$DATA_PATH.$filename);
    $json = json_decode($file, true);
    return $json;
  }
}
