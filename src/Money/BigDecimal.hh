<?hh // strict
namespace Money\Money;

class BigDecimal {
    const DEFAULT_SCALE = 2;
    protected string $value = "0";
    protected int $scale = 0;

    public function __construct(int $value = 0, ?int $scale = null) {
      if ($value instanceof BigDecimal) {
        $this->setScale($scale !== null ? $scale : $value->scale);
        $this->setValue($value->value);
      } else {
        $this->setScale($scale !== null ? $scale : self::DEFAULT_SCALE);
        $this->setValue($value);
      }
    }

    public function getValue(): string {
      return $this->value;
    }

    public function getScale(): int {
      return $this->scale;
    }

    public function __get(string $name): mixed {
      if($name === 'value') {
        return $this->value;
      } else if($name === 'scale') {
        return $this->scale;
      } else {
        throw new \InvalidArgumentException('Cannot get undefined property "'.$name.'"');
      }
    }

    public function __toString(): string {
      return $this->value;
    }

    public function toStringWith(int $scale): string {
      return $this->format($scale);
    }

    public function format(int $scale): string {
      return number_format($this->value, $scale);
    }

    public function add(string $other): BigDecimal {
      return new self(bcadd($this->value, new self($other, $this->scale), $this->scale));
    }

    public function sub(string $other): BigDecimal {
      return new self(bcsub($this->value, new self($other, $this->scale), $this->scale));
    }

    public function comp(string $other): int {
      return bccomp($this->value, new self($other, $this->scale), $this->scale);
    }

    public function gt(string $other) {
      return $this->comp(new self($other, $this->scale)) > 0;
    }

    public function gte($other) {
      return $this->comp(new self($other, $this->scale)) >= 0;
    }

    public function lt($other) {
      return $this->comp(new self($other, $this->scale)) < 0;
    }

    public function lte($other) {
      return $this->comp(new self($other, $this->scale)) <= 0;
    }

    public function mul($other) {
      return new self(bcmul($this->value, new self($other, $this->scale), $this->scale));
    }

    public function div($other): BigDecimal {
      return new self(bcdiv($this->value, new self($other, $this->scale), $this->scale));
    }

    public function mod($other): BigDecimal {
      return new self(bcmod($this->value, new self($other, $this->scale), $this->scale));
    }

    private static function getType(mixed $var): string {
      $type = gettype($var);
      if($type === 'object')
        return get_class($var);
      if($type === 'resource')
        return get_resource_type($var);
      return $type;
    }

    private function setScale(int $scale): int {
      if (!is_int($scale)) {
        throw new \InvalidArgumentException('BigDecimal scale was not int, type was: "'.getType($scale).'"');
      }
      elseif ($scale < 0) {
        throw new \InvalidArgumentException('BigDecimal scale cannot be negative value: "'.getType($scale).'"');
      }
      $this->scale = $scale;
    }

    private function setValue(mixed $value): void {
      if ($value === null) {
        throw new \InvalidArgumentException('BigDecimal value cannot be null');
      } elseif (is_string($value)) {
        if (!filter_var($value, FILTER_VALIDATE_INT)
          && !preg_match('/^[-+]?\\d+([.]\\d+)?$/u', $value)) {
          throw new \InvalidArgumentException('Invalid characters in BigDecimal constructor string: '.$value);
        }
        $this->value = bcadd($value, 0, $this->scale);
      } elseif (is_int($value)) {
        $this->value = bcadd($value, 0, $this->scale);
      } elseif (is_float($value)) {
        $this->value = bcadd($value, 0, $this->scale);
      } else {
        throw new \InvalidArgumentException('Invalid type for BigDecimal value, type was: "'.getType($value).'"');
      }
  }
}
