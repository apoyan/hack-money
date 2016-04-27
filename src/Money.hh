<?hh // decl

namespace Money;
use Money\Currency\Currency;
use Money\Money\Formatter;
use Money\Exception\CurrencyException;
use Money\Exception\MoneyException;
use Money\Money\BigDecimal as BigDecimal;

class Money {
  private $formatter;
  private $currency;
  private $_amount;

  public function __construct($obj, ?Currency $currency = null) {
    if($obj instanceof Money) {
      $this->_amount = $obj->amount();
      $this->currency = $obj->currency();
    } else {
      $this->_amount = new BigDecimal($obj);
      $this->currency = $currency;
    }
    $this->formatter = new Formatter();
  }

  public function amount() {
    return $this->_amount;
  }

  public function getAmount() {
    return $this->_amount->getValue();
  }

  public function currency() {
    return $this->currency;
  }

  public function format() {
    
  }

  public function equals(Money $other) {
    return $this->isSameCurrency($other) && $this->cents === $other->cents;
  }

  public function add(Money $other) {
    $this->assertSameCurrency($other);
    return $this->_amount->add($other->_amount);
  }

  public function sub(Money $other) {
    $this->assertSameCurrency($other);
    return new self($this->_amount->sub($other->_amount));
  }

  public function mul(Money $other) {
    $this->assertSameCurrency($other);
    return new self($this->_amount->multiply($other->_amount));
  }

  public function div(Money $other) {
    $this->assertSameCurrency($other);
    return new self($this->_amount->divide($other->_amount));
  }

  public function isSameCurrency(Money $other) {
    return $this->currency->equals($other->currency);
  }

  private function assertSameCurrency(Money $other) {
    if (!$this->isSameCurrency($other)) {
      throw new \CurrencyException('Currencies must be identical');
    }
  }
}
