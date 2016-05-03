<?hh // strict

namespace Money\Currency;
use Money\Currency\Loader as Loader;

class Currency {
  private string $decimal_mark;
  private string $html_entity;
  private string $iso_code;
  private string $iso_numeric;
  private string $name;
  private string $subunit;
  private string $symbol;
  private string $thousands_separator;
  private int $subunit_to_unit;
  private int $smallest_denomination;
  private static Map<string, Map<string, mixed>> $table = Map { };

  public function __construct(string $id) {
    if(Currency::$table->isEmpty()) {
      Currency::$table = new Map(Loader::load_currencies());
    }
    $data = Currency::$table[(string)strtolower($id)];
    $this->decimal_mark          = (string) $data["decimal_mark"];
    $this->html_entity           = (string) $data["html_entity"];
    $this->iso_code              = (string) $data["iso_code"];
    $this->iso_numeric           = (string) $data["iso_numeric"];
    $this->name                  = (string) $data["name"];
    $this->smallest_denomination = (int)    $data["smallest_denomination"];
    $this->subunit               = (string) $data["subunit"];
    $this->subunit_to_unit       = (int)    $data["subunit_to_unit"];
    $this->symbol                = (string) $data["symbol"];
    $this->thousands_separator   = (string) $data["thousands_separator"];
  }
  public function getCode(): string {
    return $this->iso_code;
  }

  public function getName(): string {
    return $this->name;
  }

  public function __toString(): string {
    return $this->getCode();
  }

  public function equals(Currency $other_currency): bool {
    return $this->iso_code === $other_currency->iso_code;
  }

  public function exponent(): int {
    return round(log10($this->subunit_to_unit));
  }
}
