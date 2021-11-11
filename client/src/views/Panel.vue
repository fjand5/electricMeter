<template>
  <div class="panel">
    <el-table :data="tableData" style="width: 90%">
      <el-table-column prop="name" label="Thông số" width="auto">
      </el-table-column>
      <el-table-column prop="value" label="Giá trị" width="auto">
      </el-table-column>
    </el-table>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
export default {
  data() {
    return {
      tableData: [
        {
          key: "getVoltage",
          name: "Điện áp",
          value: 0,
        },
        {
          key: "getCurrent",
          name: "Dòng điện",
          value: 0,
        },
        {
          key: "getPower",
          name: "Công suất",
          value: 0,
        },
        {
          key: "getFrequency",
          name: "Tần số",
          value: 0,
        },
        {
          key: "getEnergy",
          name: "Tổng số điện",
          value: 0,
        },
        {
          key: "getPf",
          name: "Hệ số công suất",
          value: 0,
        },
      ],
    };
  },
  computed: {
    ...mapGetters([
      "getVoltage",
      "getCurrent",
      "getPower",
      "getEnergy",
      "getFrequency",
      "getPf",
    ]),
  },
  mounted: function () {},
  watch: {
    getVoltage: function (n) {
      for (let i = 0; i < this.tableData.length; i++) {
        let elm = this.tableData[i];
        if (elm.key == "getVoltage") {
          elm.value = n;
          this.$set(this.tableData, i, elm);
        }
      }
    },
    getCurrent: function (n) {
      for (let i = 0; i < this.tableData.length; i++) {
        let elm = this.tableData[i];
        if (elm.key == "getCurrent") {
          elm.value = n;
          this.$set(this.tableData, i, elm);
        }
      }
    },
    getPower: function (n) {
      for (let i = 0; i < this.tableData.length; i++) {
        let elm = this.tableData[i];
        if (elm.key == "getPower") {
          elm.value = n;
          this.$set(this.tableData, i, elm);
        }
      }
    },
    getEnergy: function (n) {
      for (let i = 0; i < this.tableData.length; i++) {
        let elm = this.tableData[i];
        if (elm.key == "getEnergy") {
          elm.value = n;
          this.$set(this.tableData, i, elm);
        }
      }
    },
    getFrequency: function (n) {
      for (let i = 0; i < this.tableData.length; i++) {
        let elm = this.tableData[i];
        if (elm.key == "getFrequency") {
          elm.value = n;
          this.$set(this.tableData, i, elm);
        }
      }
    },
    getPf: function (n) {
      for (let i = 0; i < this.tableData.length; i++) {
        let elm = this.tableData[i];
        if (elm.key == "getPf") {
          elm.value = n;
          this.$set(this.tableData, i, elm);
        }
      }
    },
  },
  methods: {},
};
</script>

<style>
</style>