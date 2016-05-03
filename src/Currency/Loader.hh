<?hh //strict

namespace Money\Currency;

class Loader {
  public static string $DATA_PATH = "/../../resources/";
  private static Map<string, Map<string, mixed>> $currencies = Map { };

  public static function load_currencies(): Map<string, Map<string,mixed>> {
    return Loader::parse_currency_file("currency_iso.json")
      ->setAll(Loader::parse_currency_file("currency_non_iso.json"))
      ->setAll(Loader::parse_currency_file("currency_backwards_compatible.json"));
  }

  public static function parse_currency_file(string $filename): Map<string, Map<string,mixed>> {
    $file = file_get_contents(dirname(__FILE__).Loader::$DATA_PATH.$filename);
    return new Map(json_decode($file, true));
  }
}
