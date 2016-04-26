<?php
namespace Money\Money;

class BigDecimal {
    const DEFAULT_SCALE = 2;
    protected $value;
    protected $scale;

    public function __construct($value = 0, $scale = null) {
      if ($value instanceof BigDecimal) {
        $this->setScale($scale !== null ? $scale : $value->scale);
        $this->setValue($value->value);
      } else {
        $this->setScale($scale !== null ? $scale : self::DEFAULT_SCALE);
        $this->setValue($value);
      }
    }

    public static function toArray(array $items, $allowNullValues = false) {
      $results = array();
      try {
        foreach ($items as $key => $val) {
          if ($allowNullValues && $val === null) {
            $results[] = null;
          } elseif ($val === null) {
            throw new \InvalidArgumentException('Null value found in provided array');
          } elseif (!$val instanceof BigDecimal) {
            $results[] = new self($val);
          } else {
            $results[] = $val;
          }
        }
      }
      catch(\Exception $e) {
        throw new \InvalidArgumentException('Element at index '.$key.' could not be converted to BigDecimal!', 42, $e);
      }
      return $results;
    }

    public static function toArrayWithScale(array $items, $scale, $allowNullValues=false) {
      $results = array();
      try {
        foreach ($items as $key => $val) {
          if ($allowNullValues && $val === null) {
            $results[] = null;
          } elseif ($val === null) {
            throw new InvalidArgumentException('Null value found in provided array');
          } else {
            $results[] = new self($val, $scale);
          }
        }
      }
      catch(\Exception $e) {
        throw new \InvalidArgumentException('Element at index '.$key.' could not be converted to BigDecimal!', 42, $e);
      }
      return $results;
    }

    public function getValue() {
      return $this->value;
    }

    public function getScale() {
      return $this->scale;
    }

    public function __get($name) {
      if($name === 'value') {
        return $this->value;
      } else if($name === 'scale') {
        return $this->scale;
      } else {
        throw new \InvalidArgumentException('Cannot get undefined property "'.$name.'"');
      }
    }

    public function __toString() {
      return $this->value;
    }

    public function toStringWith($scale) {
      return $this->format($scale);
    }

    public function format($scale) {
      return number_format($this->value, $scale);
    }

    public function add($other) {
      return new self(bcadd($this->value, new self($other, $this->scale), $this->scale));
    }

    public function sub($other) {
      return new self(bcsub($this->value, new self($other, $this->scale), $this->scale));
    }

    public function comp($other) {
      return bccomp($this->value, new self($other, $this->scale), $this->scale);
    }

    public function gt($other) {
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

    public function div($other) {
      return new self(bcdiv($this->value, new self($other, $this->scale), $this->scale));
    }

    public function mod($other) {
      return new self(bcmod($this->value, new self($other, $this->scale), $this->scale));
    }

    private static function getType($var) {
      $type = gettype($var);
      if($type === 'object')
        return get_class($var);
      if($type === 'resource')
        return get_resource_type($var);
      return $type;
    }

    private function setScale($scale) {
      if (!is_int($scale)) {
        throw new \InvalidArgumentException('BigDecimal scale was not int, type was: "'.getType($scale).'"');
      }
      elseif ($scale < 0) {
        throw new \InvalidArgumentException('BigDecimal scale cannot be negative value: "'.getType($scale).'"');
      }
      $this->scale = $scale;
    }
    
    private function setValue($value) {
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
