{
  "targets": [
    {
      "target_name": "windows_process_info",
      "sources": [
        "src/addon.cc",
        "src/process.cc",
        "src/worker.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
